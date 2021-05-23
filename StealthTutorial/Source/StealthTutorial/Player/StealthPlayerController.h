// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StealthPlayerController.generated.h"

class AHitman;

/**
 * 
 */
UCLASS()
class STEALTHTUTORIAL_API AStealthPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStealthPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UClass* HitmanBlueprint;

	UPROPERTY()
	AHitman* Hitman;
};
