// Copyright 2021. Elysia-ff

#pragma once

#include "LineOfSight/ViewCastInfo.hpp"

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "LosComponent.generated.h"

class ISpottable;

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

	void RegisterSpottableObject(const TScriptInterface<ISpottable>& NewInterface);

private:
	void DrawMesh();

	void AddLineOfSightPoints();

	void AddNearSightPoints();

	FVector GetDirection(float AngleInDegrees) const;

	FViewCastInfo ViewCast(float AngleInDegrees, float Distance) const;

	void FindEdge(FViewCastInfo ViewCastA, FViewCastInfo ViewCastB, float Distance);

	void FindActorsInSight();

	bool IsInSight(const TScriptInterface<ISpottable>& Target) const;

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

	UPROPERTY(EditAnywhere, Category = "Line Of Sight")
	float SpotInterval;

private:
	TArray<FVector> ViewPoints;

	TArray<FVector> Vertices;

	TArray<int32> Triangles;

	TArray<FVector> Normals;

	TArray<FVector2D> UV0;

	TArray<FLinearColor> VertexColors;

	TArray<FProcMeshTangent> Tangents;

	UPROPERTY()
	TArray<TScriptInterface<ISpottable>> SpotCandidates;

	UPROPERTY()
	TArray<TScriptInterface<ISpottable>> SpottedList;

	FTimerHandle SpotTimer;
};
