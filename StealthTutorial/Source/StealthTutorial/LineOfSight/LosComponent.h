// Copyright 2021. Elysia-ff

#pragma once

#include "LineOfSight/ViewCastInfo.hpp"

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "LosComponent.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHTUTORIAL_API ULosComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()
	
public:
	ULosComponent(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void DrawMesh();

	void AddLineOfSightPoints();

	void AddNearSightPoints();

	FVector GetDirection(float AngleInDegrees) const;

	FViewCastInfo ViewCast(float AngleInDegrees, float Distance) const;

	void FindEdge(FViewCastInfo ViewCastA, FViewCastInfo ViewCastB, float Distance);

public:
	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Debug")
	UMaterialInterface* DebugMaterial;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Debug")
	bool bDrawDebugLine;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Far", meta = (UIMin = 0, UIMax = 360))
	int32 FarSightAngle = 0;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Far", meta = (UIMin = 2))
	int32 FarViewCastCount = 2;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Far", meta = (UIMin = 0))
	float FarDistance = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Near", meta = (UIMin = 2))
	int32 NearViewCastCount = 2;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Near", meta = (UIMin = 0))
	float NearDistance = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight|Edge")
	float EdgeFindingThreshold = 0.01f;

private:
	UPROPERTY()
	TArray<FVector> ViewPoints;

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;

	UPROPERTY()
	TArray<FVector> Normals;

	UPROPERTY()
	TArray<FVector2D> UV0;

	UPROPERTY()
	TArray<FLinearColor> VertexColors;

	UPROPERTY()
	TArray<FProcMeshTangent> Tangents;
};
