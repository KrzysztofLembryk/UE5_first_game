// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnMoveComponentReachEndPointSignature, 
	bool, 
	IsTopEndpoint
);

UCLASS( ClassGroup=(MyComponents), meta=(BlueprintSpawnableComponent) )
class MYFIRSTGAME_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

	UFUNCTION(BlueprintCallable)
	void EnableMovement(bool ShouldMove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	/**
	 * float DeltaTime - time in seconds since the last tick; used to make updates 
	 * frame-rate independent
	 * ELevelTick TickType - ENUM describing type of tick, i.e. LEVELTICK_ALL
	 * FActorComponentTickFunction* ThisTickFunction - Pointer to the tick function 
	 * struct for this component
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

	UPROPERTY(EditAnywhere)
	bool MoveEnable = false;

	UPROPERTY(BlueprintAssignable)
	FOnMoveComponentReachEndPointSignature OnEndpointReached;

	FVector StartRelativeLoc;
	FVector MoveOffsetNorm;
	float MaxDistance = 0.0;
	float CurrDistance = 0.0;
	float currDirection = 1.0;
		
};
