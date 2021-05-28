// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnManager.generated.h"

class AEnemy;

UCLASS()
class STEALTHTUTORIAL_API AEnemySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnManager(const FObjectInitializer& ObjectInitializer);

	void BeginSpawn();

	const TArray<AEnemy*>* GetEnemies() const;

private:
	void SpawnEnemy(const FTransform& SpawnTransform);

public:
	UPROPERTY(EditAnywhere, Category = "Spawn Position")
	TArray<TWeakObjectPtr<AActor>> SpawnPoses;

private:
	UPROPERTY()
	UClass* EnemyBlueprint;

	UPROPERTY()
	TArray<AEnemy*> Enemies;
};
