// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	this->CameraMesh = 
		CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainPawnCameraMesh"));
	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainPawnCamera"));

	// Setup Camera
	this->Camera->FieldOfView = 120.f;
	this->Camera->SetupAttachment(this->CameraMesh);
	this->Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 150.0f));
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGameCharacter::MoveRight(float movementDelta)
{
	FVector newLoc = GetActorLocation();
	newLoc.Y += movementDelta * this->MovementSpeed;

	SetActorLocation(newLoc);
}

void AGameCharacter::MoveForward(float movementDelta)
{
	FVector newLoc = GetActorLocation();
	newLoc.X += movementDelta * this->MovementSpeed;

	SetActorLocation(newLoc);
}

void AGameCharacter::Jump()
{
	if (!this->isJumping)
	{
		this->isJumping = true;
		FVector currLoc = GetActorLocation();
		this->startZ = currLoc.Z;
	}
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->isJumping)
	{
		this->currOffset += DeltaTime * this->JumpSpeed * float(this->currDirection);

		if (
			this->currDirection == MoveDirection::UP 
			&& this->currOffset >= this->MaxJumpHeight
		)
		{
			this->currOffset = this->MaxJumpHeight;
			this->currDirection = MoveDirection::DOWN;
		}
		else if (
			this->currDirection == MoveDirection::DOWN 
			&& this->currOffset <= 0
		)
		{
			this->currOffset = 0;
			this->currDirection = MoveDirection::UP;
			this->isJumping = false;
		}

		FVector newLoc = GetActorLocation();
		UE_LOG(LogTemp, Display, TEXT("Tick, prev loc: %s, curr offset: %f"), *newLoc.ToString(), this->currOffset);
		newLoc.Z = this->startZ + this->currOffset;
		SetActorLocation(newLoc);
	}
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// Register LR movement
		PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGameCharacter::MoveRight);
	
		// Register UD movement
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGameCharacter::MoveForward);
	
		// Register Jump
		PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AGameCharacter::Jump);
	}
}

