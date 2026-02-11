// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAME_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMyGameStateBase();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	// Time in seconds
	UPROPERTY()
	float TimeLeftInSession = 0.0;

	friend class AMyGameModeBase;
};
