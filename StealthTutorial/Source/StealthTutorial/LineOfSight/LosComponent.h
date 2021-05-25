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

	void AddLineOfSightPoints(TArray<FVector>* ViewPoints);

	void AddNearSightPoints(TArray<FVector>* ViewPoints);

	FVector GetDirection(float AngleInDegrees) const;

	FViewCastInfo ViewCast(float AngleInDegrees, float Distance) const;

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
};
