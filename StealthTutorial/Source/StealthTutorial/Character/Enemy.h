// Copyright 2021. Elysia-ff

#pragma once

#include "LineOfSight/SpottableInterface.h"

#include "CoreMinimal.h"
#include "Character/StealthCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHTUTORIAL_API AEnemy : public AStealthCharacter, public ISpottable
{
	GENERATED_BODY()

public:
	AEnemy(const FObjectInitializer& ObjectInitializer);

	virtual FVector GetSpotPointLocation() const override;

	virtual void OnBeginSpotted() override;

	virtual void OnEndSpotted() override;

private:
	void TurnOutlineOn();

	void TurnOutlineOff();

public:
	UPROPERTY(VisibleAnywhere, Category = "Line Of Sight")
	USceneComponent* SpotPoint;

	UPROPERTY(EditAnywhere, Category = "Line Of Sight")
	float OutlineDuration;

private:
	FTimerHandle OutlineTimer;
};
