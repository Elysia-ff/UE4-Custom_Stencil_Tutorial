// Copyright 2021. Elysia-ff


#include "Hitman.h"

#include "Character/Controller/HitmanAIController.h"
#include "LineOfSight/LosComponent.h"

AHitman::AHitman(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AHitmanAIController::StaticClass();

	LosComponent = CreateDefaultSubobject<ULosComponent>(TEXT("LosComponent"));
	LosComponent->SetupAttachment(RootComponent);
}
