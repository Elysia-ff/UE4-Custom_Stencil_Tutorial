// Copyright 2021. Elysia-ff


#include "Hitman.h"

#include "Character/Controller/HitmanAIController.h"

AHitman::AHitman(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AHitmanAIController::StaticClass();
}
