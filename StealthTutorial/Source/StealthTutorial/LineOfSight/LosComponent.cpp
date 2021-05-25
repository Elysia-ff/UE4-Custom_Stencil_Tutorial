// Copyright 2021. Elysia-ff


#include "LosComponent.h"

#include <Engine/Public/DrawDebugHelpers.h>

#include "StealthTypes.hpp"

ULosComponent::ULosComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULosComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DebugMaterial != nullptr)
	{
		SetMaterial(0, DebugMaterial);
	}
}

void ULosComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawMesh();
}

void ULosComponent::DrawMesh()
{
	TArray<FVector> ViewPoints;
	AddLineOfSightPoints(&ViewPoints);
	AddNearSightPoints(&ViewPoints);

	TArray<FVector> Vertices;
	Vertices.Reserve(ViewPoints.Num() + 1);
	Vertices.Add(FVector::ZeroVector);

	TArray<int32> Triangles;
	Triangles.Reserve((ViewPoints.Num() - 1) * 3);

	int32 ViewPointsNum = ViewPoints.Num();
	for (int32 i = 0; i < ViewPointsNum; i++)
	{
		if (bDrawDebugLine)
		{
			DrawDebugLine(GetWorld(), GetComponentLocation(), ViewPoints[i], FColor::Black, false, (-1.0f), (uint8)'\000', 1.0f);
		}

		Vertices.Add(GetComponentTransform().InverseTransformPosition(ViewPoints[i]));

		if (i < ViewPointsNum - 1)
		{
			Triangles.Add(0);
			Triangles.Add(i + 2);
			Triangles.Add(i + 1);
		}
	}

	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;
	CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
}

void ULosComponent::AddLineOfSightPoints(TArray<FVector>* ViewPoints)
{
	check(ViewPoints);
	check(FarViewCastCount >= 2);

	float StartAngle = -FarSightAngle * 0.5f;
	float DeltaAngle = (float)FarSightAngle / (FarViewCastCount - 1);

	for (int32 i = 0; i < FarViewCastCount; i++)
	{
		float Angle = StartAngle + (DeltaAngle * i);
		FViewCastInfo ViewCastInfo = ViewCast(Angle, FarDistance);

		ViewPoints->Add(ViewCastInfo.Point);
	}
}

void ULosComponent::AddNearSightPoints(TArray<FVector>* ViewPoints)
{
	check(ViewPoints);
	check(NearViewCastCount >= 2);

	float NearSightAngle = 360.0f - FarSightAngle;
	float StartAngle = FarSightAngle * 0.5f;
	float DeltaAngle = NearSightAngle / (NearViewCastCount - 1);

	for (int32 i = 0; i < NearViewCastCount; i++)
	{
		float Angle = StartAngle + (DeltaAngle * i);
		FViewCastInfo ViewCastInfo = ViewCast(Angle, NearDistance);

		ViewPoints->Add(ViewCastInfo.Point);
	}
}

FVector ULosComponent::GetDirection(float AngleInDegrees) const
{
	FVector ForwardVector = GetForwardVector();
	
	return ForwardVector.RotateAngleAxis(AngleInDegrees, GetUpVector());
}

FViewCastInfo ULosComponent::ViewCast(float AngleInDegrees, float Distance) const
{
	FVector Dir = GetDirection(AngleInDegrees);
	FVector LineStart = GetComponentLocation();
	FVector LineEnd = LineStart + (Dir * Distance);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_ObstacleTrace))
	{
		return FViewCastInfo(HitResult.ImpactPoint);
	}
	
	return FViewCastInfo(LineEnd);
}
