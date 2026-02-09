// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpEnum.h"
#include "JumpActor.generated.h"


UCLASS()
class MYFIRSTGAME_API AJumpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Mesh Component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* JumpMesh;
	
	// Settings 
	UPROPERTY(EditAnywhere, Category = "Jump Settings")
	float MaxJumpHeight = 100.0;
	
	UPROPERTY(EditAnywhere, Category = "Jump Settings")
	float JumpSpeed = 50.0;

	UPROPERTY(EditAnywhere, Category = "Jump Settings")
	float JumpOffset = 0.0;

private:
	// Position where actor was spawned
	FVector startPos;
	// Current offset relative to start
	float currOffset = 0.0;
	// Direction in which the jump is beeing executed
	JumpDirection currDirection = JumpDirection::UP;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
