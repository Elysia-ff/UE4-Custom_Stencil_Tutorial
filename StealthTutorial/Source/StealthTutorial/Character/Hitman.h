// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "Character/StealthCharacter.h"
#include "Hitman.generated.h"

class ULosComponent;

/**
 * 
 */
UCLASS()
class STEALTHTUTORIAL_API AHitman : public AStealthCharacter
{
	GENERATED_BODY()
	
public:
	AHitman(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(VisibleAnywhere, Category = "Line Of Sight")
	ULosComponent* LosComponent;
};
