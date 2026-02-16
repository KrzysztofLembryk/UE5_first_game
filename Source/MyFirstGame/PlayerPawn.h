// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "PlayerPawn.generated.h"

/**
 * Forward declarations. Why? Their full definitions are in Unreal Engine’s source code and 
 * headers. You use forward declarations when you only need pointers or references, and 
 * include their headers (like "InputAction.h" or "InputMappingContext.h") when you need 
 * their full functionality.
 */
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class MYFIRSTGAME_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()
	
public:

	// Changing speed to acceleration per second, because now, ADefaultPawn gives us a 
	// FloatingPawnMovement component, which handles movement by adding acceleration to the 
	// pawn, instead of setting a velocity directly.
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float AccelerationPerSecond = 100.0f;

	UPROPERTY(EditAnywhere, Category = "EI Settings")
	TObjectPtr<UInputMappingContext> PlayerMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "EI Settings")
	TObjectPtr<UInputAction> MovementInputAction;

	UPROPERTY(EditAnywhere, Category = "EI Settings")
	TObjectPtr<UInputAction> CameraInputAction;

	UFUNCTION(BlueprintCallable)
	void ConsumeMonster(AActor *Actor);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleMovementInput(const FInputActionValue& InputValue);
	void HandleCameraInput(const FInputActionValue& InputValue);
};
