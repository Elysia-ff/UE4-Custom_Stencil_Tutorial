// Copyright 2021. Elysia-ff


#include "Player/StealthPlayerCamera.h"

#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AStealthPlayerCamera::AStealthPlayerCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
}

// Called every frame
void AStealthPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MoveInput.IsZero())
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X += MoveInput.X * MoveSpeed * DeltaTime;
		NewLocation.Y += MoveInput.Y * MoveSpeed * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AStealthPlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AStealthPlayerCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStealthPlayerCamera::MoveRight);
}

void AStealthPlayerCamera::AddMoveInput(const FVector2D& Value)
{
	MoveInput.X = FMath::Clamp(MoveInput.X + Value.X, -1.0f, 1.0f);
	MoveInput.Y = FMath::Clamp(MoveInput.Y + Value.Y, -1.0f, 1.0f);
}

void AStealthPlayerCamera::MoveForward(float AxisValue)
{
	MoveInput.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void AStealthPlayerCamera::MoveRight(float AxisValue)
{
	MoveInput.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}
