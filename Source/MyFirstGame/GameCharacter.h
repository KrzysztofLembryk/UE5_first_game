// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameCharacter.generated.h"


UCLASS()
class MYFIRSTGAME_API AGameCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameCharacter();
	void MoveLR(float movementDelta);
	void MoveUD(float movementDelta);
	void Jump(float movementDelta);

protected:
	// #### VARIABLES ####
	// Main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CameraMesh;

	// Movement speed 
	UPROPERTY(EditAnywhere, Category = "Character Movement Settings")
	float MovementSpeed = 1.0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
