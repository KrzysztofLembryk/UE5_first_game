// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster.h"

void APlayerPawn::ConsumeMonster(AActor *Actor)
{
    if (AMonster *Monster = Cast<AMonster>(Actor))
    {
        Monster->Destroy();
    }
}


void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // APlayerController is a class in Unreal Engine that represents the player’s controller in the game. It handles player input, manages the camera, and controls the pawn (character or vehicle) that the player possesses.

    // Key points:

    // It processes input from the player (keyboard, mouse, gamepad).
    // It can possess and control a pawn (such as a character).
    // It manages HUD, camera, and player-specific logic.
    // Each player in the game typically has their own APlayerController instance.

    // Gets the controller for this pawn.
    // Casts it to APlayerController (the player’s controller type).
    // If the cast fails, PlayerController will be nullptr.
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found in PlayerPawn"));
        return;
    }

    // Gets the LocalPlayer object from the PlayerController.
    // Uses GetSubsystem to get the Enhanced Input subsystem for this player.
    // This subsystem manages input mapping contexts.
    // Adding InputMappingContext asset to EI subsystem (we enable it)
    UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::
        GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer()
            );

    if (!EISubsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("EnhancedInputLocalPlayerSubsystem not found in PlayerPawn"));
        return;
    }

    if (!PlayerMappingContext || !MovementInputAction || !CameraInputAction)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerMappingContext or InputActions not set in PlayerPawn"));
        return;
    }
    
    EISubsystem->AddMappingContext(PlayerMappingContext, 0);

    UEnhancedInputComponent *EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    if (!EIC)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is not EnhancedInputComponent"));
        return;
    }

    EIC->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &APlayerPawn::HandleMovementInput);

    EIC->BindAction(CameraInputAction, ETriggerEvent::Triggered, this, &APlayerPawn::HandleCameraInput);
}

void APlayerPawn::HandleMovementInput(const FInputActionValue& InputValue)
{
    const EInputActionValueType InputType = InputValue.GetValueType();

    switch (InputType)
    {
    case EInputActionValueType::Axis2D:
    {

        float DeltaTimeSeconds = GetWorld()->GetDeltaSeconds();
        FInputActionValue::Axis2D XYDelta = InputValue.Get<FInputActionValue::Axis2D>();

        XYDelta = XYDelta * DeltaTimeSeconds * this->AccelerationPerSecond;

        FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetController()->GetControlRotation());
        ForwardVector.Normalize();

        FVector RightVector = UKismetMathLibrary::GetRightVector(GetController()->GetControlRotation());
        RightVector.Normalize();

        ForwardVector *= XYDelta.X;
        RightVector *= XYDelta.Y;

        AddMovementInput(ForwardVector, 1.f, false);
        AddMovementInput(RightVector, 1.f, false);
        break;
    }
    default:
        break;
    }
}

void APlayerPawn::HandleCameraInput(const FInputActionValue& InputValue)
{ 
    const EInputActionValueType InputType = InputValue.GetValueType();

    switch (InputType)
    {
    case EInputActionValueType::Axis2D:
        {
            FInputActionValue::Axis2D MouseXYDelta = InputValue.Get<FInputActionValue::Axis2D>();

            AddControllerYawInput(MouseXYDelta.X);
            AddControllerPitchInput(-MouseXYDelta.Y); 
            break;
        }
    default:
        break;
    }
}
