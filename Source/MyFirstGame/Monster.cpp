// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "BoidSubsystem.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	UBoidSubsystem *BoidSubSys = GetWorld()->GetSubsystem<UBoidSubsystem>();

	if(!BoidSubSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonster::BeginPlay - Boid subsystem not found!"));
		return;
	}

	BoidSubSys->RegisterActor(this);
}

void AMonster::Destroyed()
{
	UBoidSubsystem *BoidSubSys = GetWorld()->GetSubsystem<UBoidSubsystem>();

	if(!BoidSubSys)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonster::Destroyed - Boid subsystem not found!"));
		return;
	}

	BoidSubSys->UnRegisterActor(this);

	Super::Destroyed();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

