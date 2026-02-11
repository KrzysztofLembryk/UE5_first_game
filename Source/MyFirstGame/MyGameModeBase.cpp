// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyGameStateBase.h"

AMyGameModeBase::AMyGameModeBase()
{
    GameStateClass = AMyGameStateBase::StaticClass();
    DefaultPawnClass = AGameCharacter::StaticClass();
}

void AMyGameModeBase::InitGameState() 
{
    Super::InitGameState();

    if (AMyGameStateBase *MyGameState = Cast<AMyGameStateBase>(GameState))
    {
        MyGameState->TimeLeftInSession = this->GameSessionAllowedTimeSeconds;
    }
}