// Copyright 2021. Elysia-ff


#include "StealthPlayerController.h"

#include <Engine/Public/EngineUtils.h>

#include "Character/Controller/HitmanAIController.h"
#include "Character/Hitman.h"
#include "Player/StealthPlayerCamera.h"
#include "SpawnManager/EnemySpawnManager.h"

AStealthPlayerController::AStealthPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> HitmanObjectFinder(TEXT("Blueprint'/Game/Blueprint/Character/BP_Hitman.BP_Hitman_C'"));
	check(HitmanObjectFinder.Succeeded());
	HitmanBlueprint = HitmanObjectFinder.Object;
}

void AStealthPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	AStealthPlayerCamera* PossessedPawn = GetPawn<AStealthPlayerCamera>();
	if (PossessedPawn != nullptr && GEngine != nullptr)
	{
		FVector2D MouseInput;
		if (GetMousePosition(MouseInput.X, MouseInput.Y))
		{
			FVector2D MoveInput;
			const FIntPoint ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();
			
			if (MouseInput.X <= PossessedPawn->EdgePixel)
			{
				MoveInput.Y = -1.0f;
			}
			else if (MouseInput.X >= ViewportSize.X - PossessedPawn->EdgePixel)
			{
				MoveInput.Y = 1.0f;
			}

			if (MouseInput.Y <= PossessedPawn->EdgePixel)
			{
				MoveInput.X = 1.0f;
			}
			else if (MouseInput.Y >= ViewportSize.Y - PossessedPawn->EdgePixel)
			{
				MoveInput.X = -1.0f;
			}

			if (!MoveInput.IsZero())
			{
				PossessedPawn->AddMoveInput(MoveInput);
			}
		}
	}

	if (bOnRMB)
	{
		MoveHitmanToMouseCursor();
	}
}

AHitman* AStealthPlayerController::GetHitman() const
{
	check(Hitman);

	return Hitman;
}

void AStealthPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(HitmanBlueprint);

	FActorSpawnParameters Param;
	Param.Owner = this;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Hitman = GetWorld()->SpawnActor<AHitman>(HitmanBlueprint, FVector(0.0f, 0.0f, 90.0f), FRotator::ZeroRotator, Param);
	check(Hitman);
	Hitman->SpawnDefaultController();

	TActorIterator<AEnemySpawnManager> Iterator(GetWorld());
	if (Iterator)
	{
		Iterator->BeginSpawn();
	}
}

void AStealthPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RMB", IE_Pressed, this, &AStealthPlayerController::OnRMBPressed);
	InputComponent->BindAction("RMB", IE_Released, this, &AStealthPlayerController::OnRMBReleased);
}

void AStealthPlayerController::OnRMBPressed()
{
	bOnRMB = true;
}

void AStealthPlayerController::OnRMBReleased()
{
	bOnRMB = false;
}

void AStealthPlayerController::MoveHitmanToMouseCursor()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		FVector TargetLocation = HitResult.ImpactPoint;

		check(Hitman && Hitman->GetController<AHitmanAIController>());
		Hitman->GetController<AHitmanAIController>()->MoveToLocation(TargetLocation);
	}
}
