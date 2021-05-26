// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "Character/StealthCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHTUTORIAL_API AEnemy : public AStealthCharacter
{
	GENERATED_BODY()

public:
	AEnemy(const FObjectInitializer& ObjectInitializer);
};
