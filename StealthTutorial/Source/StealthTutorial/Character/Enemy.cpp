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

void AEnemy::OnBeginSpotted()
{
	GetWorldTimerManager().ClearTimer(OutlineTimer);
	TurnOutlineOn();
}

void AEnemy::OnEndSpotted()
{
	if (OutlineDuration <= 0.0f)
	{
		TurnOutlineOff();
	}
	else
	{
		GetWorldTimerManager().SetTimer(OutlineTimer, this, &AEnemy::TurnOutlineOff, OutlineDuration);
	}
}

void AEnemy::TurnOutlineOn()
{
	if (GetMesh())
	{
		GetMesh()->SetCustomDepthStencilValue(2);
	}
}

void AEnemy::TurnOutlineOff()
{
	if (GetMesh())
	{
		GetMesh()->SetCustomDepthStencilValue(0);
	}
}
