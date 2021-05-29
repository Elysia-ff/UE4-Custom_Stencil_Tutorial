// Copyright 2021. Elysia-ff

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StealthPlayerCamera.generated.h"

class UCameraComponent;

UCLASS()
class STEALTHTUTORIAL_API AStealthPlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStealthPlayerCamera(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddMoveInput(const FVector2D& Value);

private:
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float EdgePixel;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

private:
	FVector2D MoveInput;
};
