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

	AHitman* GetHitman() const;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void OnRMBPressed();

	void OnRMBReleased();

	void MoveHitmanToMouseCursor();

private:
	UPROPERTY()
	UClass* HitmanBlueprint;

	UPROPERTY()
	AHitman* Hitman;

	bool bOnRMB;
};
