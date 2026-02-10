// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UMoveComponent::EnableMovement(bool ShouldMove)
{
	this->MoveEnable = ShouldMove;
	SetComponentTickEnabled(this->MoveEnable);
}

// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set start and end locations
	this->StartRelativeLoc = GetRelativeLocation();
	this->MoveOffsetNorm = this->MoveOffset;
	this->MoveOffsetNorm.Normalize();
	this->MaxDistance = this->MoveOffset.Length();
	// Check if ticking is required
	SetComponentTickEnabled(this->MoveEnable);
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->MoveEnable)
	{
		this->CurrDistance += DeltaTime * this->Speed * this->currDirection;
	
		if (this->CurrDistance >= this->MaxDistance || this->CurrDistance <= 0)
		{
			this->currDirection *= -1;
			this->OnEndpointReached.Broadcast(
				this->CurrDistance >= this->MaxDistance
			);
			this->CurrDistance = FMath::Clamp(this->CurrDistance, 0, this->MaxDistance);
		}

		SetRelativeLocation(this->StartRelativeLoc + this->MoveOffsetNorm * this->CurrDistance);
	}
}

