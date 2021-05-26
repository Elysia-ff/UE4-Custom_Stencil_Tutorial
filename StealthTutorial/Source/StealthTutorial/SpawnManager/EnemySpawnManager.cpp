// Copyright 2021. Elysia-ff


#include "EnemySpawnManager.h"

#include "Character/Enemy.h"

// Sets default values
AEnemySpawnManager::AEnemySpawnManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UClass> EnemyObjectFinder(TEXT("Blueprint'/Game/Blueprint/Character/BP_Enemy.BP_Enemy_C'"));
	check(EnemyObjectFinder.Succeeded());
	EnemyBlueprint = EnemyObjectFinder.Object;
}

const TArray<AEnemy*>* AEnemySpawnManager::GetEnemies() const
{
	return &Enemies;
}

// Called when the game starts or when spawned
void AEnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	Enemies.Reserve(SpawnPoses.Num());
	for (int32 i = 0; i < SpawnPoses.Num(); i++)
	{
		if (!SpawnPoses[i].IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid spawn position : %d"), i);
			continue;
		}

		SpawnEnemy(SpawnPoses[i]->GetTransform());
	}
}

void AEnemySpawnManager::SpawnEnemy(const FTransform& SpawnTransform)
{
	check(EnemyBlueprint);
	
	FActorSpawnParameters Param;
	Param.Owner = this;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemy* NewEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyBlueprint, SpawnTransform, Param);
	check(NewEnemy);

	NewEnemy->SpawnDefaultController();
	Enemies.Add(NewEnemy);
}
