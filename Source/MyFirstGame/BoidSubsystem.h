// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BoidSubsystem.generated.h"

struct FBoid
{
	uint32_t Id;
	FVector Position;
	FVector Velocity;
};

/**
 * 
 */
UCLASS()
class MYFIRSTGAME_API UBoidSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	UBoidSubsystem();
	// UWorldSubsystem interface
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	// UTickableWorldSubsystem interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	void RegisterActor(AActor* Actor, uint32 *ActorId);
	bool UnRegisterActor(uint32 ActorId);

protected:
	FVector ApplySeparation(const FBoid& Boid);
	FVector ApplyAlignment(const FBoid& Boid);
	FVector ApplyCohesion(const FBoid& Boid);
	FVector LimitVectorLength(const FVector& Vector, float MaxSize);
	
private:
	uint32_t NextBoidId = 0;
	TArray<FBoid> Boids;
	float NeighbourRadius; 
	float SeparationWeight; 
	float AlignmentWeight; 
	float CohesionWeight; 
	float MaxSpeed; 
	float MaxForce; 
	
	UPROPERTY()
	TMap<uint32, AActor*> BoidActorMap;
};
