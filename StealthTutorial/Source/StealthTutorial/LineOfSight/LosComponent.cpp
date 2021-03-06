// Copyright 2021. Elysia-ff


#include "LosComponent.h"

#include <Engine/Public/DrawDebugHelpers.h>

#include "LineOfSight/SpottableInterface.h"
#include "StealthTypes.hpp"

ULosComponent::ULosComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	SetCastShadow(false);
	SetCollisionProfileName(TEXT("NoCollision"));
}

void ULosComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DebugMaterial != nullptr)
	{
		SetMaterial(0, DebugMaterial);
	}

	if (SpotInterval > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(SpotTimer, this, &ULosComponent::FindActorsInSight, SpotInterval, true);
	}
}

void ULosComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawMesh();
}

void ULosComponent::RegisterSpottableObject(const TScriptInterface<ISpottable>& NewInterface)
{
	SpotCandidates.Add(NewInterface);
}

void ULosComponent::DrawMesh()
{
	ViewPoints.Reset();
	AddLineOfSightPoints();
	AddNearSightPoints();

	Vertices.Reset(ViewPoints.Num() + 1);
	Vertices.Add(FVector::ZeroVector);

	Triangles.Reset((ViewPoints.Num() - 1) * 3);

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

	CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
}

void ULosComponent::AddLineOfSightPoints()
{
	check(FarViewCastCount >= 2);

	float StartAngle = -FarSightAngle * 0.5f;
	float DeltaAngle = (float)FarSightAngle / (FarViewCastCount - 1);

	FViewCastInfo OldViewCast;
	for (int32 i = 0; i < FarViewCastCount; i++)
	{
		float Angle = StartAngle + (DeltaAngle * i);
		FViewCastInfo ViewCastInfo = ViewCast(Angle, FarDistance);

		if (i > 0 && OldViewCast != ViewCastInfo)
		{
			FindEdge(OldViewCast, ViewCastInfo, FarDistance);
		}

		ViewPoints.Add(ViewCastInfo.Point);
		OldViewCast = ViewCastInfo;
	}
}

void ULosComponent::AddNearSightPoints()
{
	check(NearViewCastCount >= 2);

	float NearSightAngle = 360.0f - FarSightAngle;
	float StartAngle = FarSightAngle * 0.5f;
	float DeltaAngle = NearSightAngle / (NearViewCastCount - 1);

	FViewCastInfo OldViewCast;
	for (int32 i = 0; i < NearViewCastCount; i++)
	{
		float Angle = StartAngle + (DeltaAngle * i);
		FViewCastInfo ViewCastInfo = ViewCast(Angle, NearDistance);

		if (i > 0 && OldViewCast != ViewCastInfo)
		{
			FindEdge(OldViewCast, ViewCastInfo, NearDistance);
		}

		ViewPoints.Add(ViewCastInfo.Point);
		OldViewCast = ViewCastInfo;
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
		return FViewCastInfo(HitResult.Actor, HitResult.ImpactPoint, AngleInDegrees, HitResult.ImpactNormal);
	}
	
	return FViewCastInfo(nullptr, LineEnd, AngleInDegrees, FVector_NetQuantizeNormal::ZeroVector);
}

void ULosComponent::FindEdge(FViewCastInfo ViewCastA, FViewCastInfo ViewCastB, float Distance)
{
	check(EdgeFindingThreshold > 0.0f);

	if (FMath::Abs(ViewCastA.AngleInDegrees - ViewCastB.AngleInDegrees) <= EdgeFindingThreshold)
	{
		ViewPoints.Add(ViewCastA.Point);
		ViewPoints.Add(ViewCastB.Point);
		return;
	}

	float Angle = (ViewCastA.AngleInDegrees + ViewCastB.AngleInDegrees) * 0.5f;
	FViewCastInfo NewViewCast = ViewCast(Angle, Distance);
	if (ViewCastA == NewViewCast)
	{
		FindEdge(NewViewCast, ViewCastB, Distance);
	}
	else if (ViewCastB == NewViewCast)
	{
		FindEdge(ViewCastA, NewViewCast, Distance);
	}
	else
	{
		FindEdge(ViewCastA, NewViewCast, Distance);
		FindEdge(NewViewCast, ViewCastB, Distance);
	}
}

void ULosComponent::FindActorsInSight()
{
	SpottedList.Reset();

	for (int32 i = 0; i < SpotCandidates.Num(); i++)
	{
		if (!SpotCandidates[i])
		{
			continue;
		}

		if (IsInSight(SpotCandidates[i]))
		{
			SpottedList.Add(SpotCandidates[i]);
			
			if (!SpotCandidates[i]->bIsSpotting)
			{
				SpotCandidates[i]->bIsSpotting = true;
				SpotCandidates[i]->OnBeginSpotted();
			}

			DrawDebugLine(GetWorld(), GetComponentLocation(), SpotCandidates[i]->GetSpotPointLocation(), FColor::Red, false, SpotInterval, (uint8)'\000', 5.0f);
		}
		else
		{
			if (SpotCandidates[i]->bIsSpotting)
			{
				SpotCandidates[i]->bIsSpotting = false;
				SpotCandidates[i]->OnEndSpotted();
			}
		}
	}
}

bool ULosComponent::IsInSight(const TScriptInterface<ISpottable>& Target) const
{
	FVector ComponentLocation = GetComponentLocation();
	FVector TargetLocation = Target->GetSpotPointLocation();
	TargetLocation.Z = ComponentLocation.Z;

	FVector Dir = (TargetLocation - ComponentLocation);
	float SqrDistanceToTarget = Dir.SizeSquared();

	if (SqrDistanceToTarget > FarDistance * FarDistance)
	{
		return false;
	}

	bool bInSight = false;
	if (SqrDistanceToTarget <= NearDistance * NearDistance)
	{
		bInSight = true;
	}
	else
	{
		float AngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetForwardVector(), Dir.GetSafeNormal())));
		float HalfFarSightAngle = FarSightAngle * 0.5f;

		bInSight = (-HalfFarSightAngle <= AngleInDegrees && AngleInDegrees <= HalfFarSightAngle);
	}

	if (bInSight)
	{
		check(GetOwner());

		FHitResult HitResult;
		FCollisionQueryParams Param;
		Param.AddIgnoredActor(GetOwner());

		if (GetWorld()->LineTraceSingleByChannel(HitResult, ComponentLocation, Target->GetSpotPointLocation(), ECC_Camera, Param))
		{
			if (HitResult.Actor.IsValid() && HitResult.Actor == Target.GetObject())
			{
				return true;
			}
		}
	}
	
	return false;
}
