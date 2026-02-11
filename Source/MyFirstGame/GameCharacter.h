// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MoveEnum.h"
#include "GameCharacter.generated.h"


UCLASS()
class MYFIRSTGAME_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameCharacter();
	void MoveRight(float movementDelta);
	void MoveForward(float movementDelta);
	void Jump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// #### VARIABLES ####
	// Main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CameraMesh;

	// Movement speed 
	UPROPERTY(EditAnywhere, Category = "Character Movement Settings")
	float MovementSpeed = 1.0;

	// Settings 
	UPROPERTY(EditAnywhere, Category = "Jump Settings")
	float MaxJumpHeight = 200.0;
	
	UPROPERTY(EditAnywhere, Category = "Jump Settings")
	float JumpSpeed = 350.0;

private:
	bool isJumping = false;
	float startZ = 0;
	// Current offset relative to start
	float currOffset = 0.0;
	// Direction in which the jump is beeing executed
	MoveDirection currDirection = MoveDirection::UP;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
