// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpActor.h"

// Sets default values
AJumpActor::AJumpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components
	this->JumpMesh = 
		CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JumpMesh"));
}

// Called when the game starts or when spawned
void AJumpActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Store initial pos
	this->startPos = GetActorLocation();
	this->currOffset = this->JumpOffset;
}

// Called every frame
void AJumpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	}

	FVector newPos = this->startPos;
	newPos.Z += this->currOffset;
	SetActorLocation(newPos);
}

