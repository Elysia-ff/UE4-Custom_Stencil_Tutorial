// Copyright 2021. Elysia-ff


#include "Enemy.h"

#include "Character/Controller/EnemyAIController.h"

AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	AIControllerClass = AEnemyAIController::StaticClass();

	SpotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpotPoint"));
	SpotPoint->SetupAttachment(RootComponent);
}

FVector AEnemy::GetSpotPointLocation() const
{
	return SpotPoint->GetComponentLocation();
}
