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

void AGameCharacter::MoveLR(float movementDelta)
{
	FVector newLoc = GetActorLocation();
	newLoc.Y += movementDelta * this->MovementSpeed;

	SetActorLocation(newLoc);
}

void AGameCharacter::MoveUD(float movementDelta)
{
	FVector newLoc = GetActorLocation();
	newLoc.X += movementDelta * this->MovementSpeed;

	SetActorLocation(newLoc);
}

void AGameCharacter::Jump(float movementDelta)
{
	FVector newLoc = GetActorLocation();
	newLoc.Z += movementDelta * this->MovementSpeed;

	SetActorLocation(newLoc);
}


// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Register LR movement
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AGameCharacter::MoveLR);

	// Register UD movement
	PlayerInputComponent->BindAxis(TEXT("MoveUD"), this, &AGameCharacter::MoveUD);

	// Register Jump
	PlayerInputComponent->BindAxis(TEXT("Jump"), this, &AGameCharacter::Jump);
}

