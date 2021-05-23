// Copyright 2021. Elysia-ff


#include "StealthPlayerController.h"

#include "Player/StealthPlayerCamera.h"

AStealthPlayerController::AStealthPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
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
}