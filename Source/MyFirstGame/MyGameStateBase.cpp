// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyGameStateBase::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    if (this->TimeLeftInSession <= 0.0)
    {
        this->TimeLeftInSession = 0.0;
        UE_LOG(LogTemp, Warning, TEXT("Time left in session: %f, GAME END"), this->TimeLeftInSession);
    }
    else
    {
        this->TimeLeftInSession -= DeltaSeconds;
        // UE_LOG(LogTemp, Warning, TEXT("Time left: %f"), this->TimeLeftInSession);
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(this->TimeLeftInSession));
    }
}