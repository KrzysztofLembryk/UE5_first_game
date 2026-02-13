// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSubsystem.h"

UBoidSubsystem::UBoidSubsystem()
{
	this->NeighbourRadius = 500.0f;
	this->SeparationWeight = 1.0f;
	this->AlignmentWeight = 1.0f;
	this->CohesionWeight = 1.0f;
	this->MaxSpeed = 200.0f;
	this->MaxForce = 200.0f;
}

void UBoidSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
}

void UBoidSubsystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Copy to avoid modifying while iterating
    TArray<FBoid> CopiedBoids = this->Boids; 

    for (int32 BoidIndex = 0; BoidIndex < CopiedBoids.Num(); BoidIndex++)
    {
        FBoid &Boid = CopiedBoids[BoidIndex];

        FVector SeparationForce = this->ApplySeparation(Boid) * this->SeparationWeight;
        FVector AlignmentForce = this->ApplyAlignment(Boid) * this->AlignmentWeight;
        FVector CohesionForce = this->ApplyCohesion(Boid) * this->CohesionWeight;

        FVector Acceleration = SeparationForce + AlignmentForce + CohesionForce;
        Acceleration = this->LimitVectorLength(Acceleration, this->MaxForce);

        Boid.Velocity += Acceleration * DeltaTime;
        Boid.Velocity = this->LimitVectorLength(Boid.Velocity, this->MaxSpeed);
        Boid.Position += Boid.Velocity * DeltaTime;

        if (AActor** BoidActor = this->BoidActorMap.Find(Boid.Id))
        {
            (*BoidActor)->SetActorLocation(Boid.Position, true);
            (*BoidActor)->SetActorRotation(Boid.Velocity.Rotation());
        }
    }

    // Update original array after processing
    this->Boids = CopiedBoids;
}


/**
 * Returns a TStatId, which is used by Unreal Engine’s profiling system to track 
 * performance statistics for this subsystem
 */
TStatId UBoidSubsystem::GetStatId() const
{
    // RETURN_QUICK_DECLARE_CYCLE_STAT(UBoidSubsystem, STATGROUP_Tickables) creates and returns a stat ID for the UBoidSubsystem class, grouping it under STATGROUP_Tickables.
    // This allows Unreal Engine to measure and display how much time is spent ticking (updating) this subsystem in the profiler.
    RETURN_QUICK_DECLARE_CYCLE_STAT(UBoidSubsystem, STATGROUP_Tickables);
}


void UBoidSubsystem::RegisterActor(AActor* BoidActor)
{
    if (!BoidActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBoidSubsystem::RegisterActor - Attempted to register a null actor!"));
        return;
    }

    this->NextBoidId++;

    FBoid NewBoid;
    NewBoid.Id = this->NextBoidId;
    NewBoid.Position = BoidActor->GetActorLocation();
    NewBoid.Velocity = FVector(
        FMath::RandRange(-200, 200), 
        FMath::RandRange(-200, 200), 
        0.0f
    ); 
    this->Boids.Add(NewBoid);
    this->BoidActorMap.Add(NewBoid.Id, BoidActor);
}


void UBoidSubsystem::UnRegisterActor(AActor* BoidActor)
{
    if (!BoidActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("UBoidSubsystem::UnRegisterActor - Attempted to unregister a null actor!"));
        return;
    }
}

FVector UBoidSubsystem::ApplySeparation(const FBoid& Boid)
{
    FVector SteeringForce = FVector::ZeroVector;
    int32 NeighbourCount = 0;

    for (const FBoid& OtherBoid : this->Boids)
    {
        if (OtherBoid.Id != Boid.Id)
        {
            float Distance = FVector::Dist(Boid.Position, OtherBoid.Position);

            if (Distance < this->NeighbourRadius)
            {
                // Repulsion is stronger the closer the neighbor is
                FVector RepulsionDirection = Boid.Position - OtherBoid.Position;

                if (!RepulsionDirection.IsNearlyZero())
                {
                    RepulsionDirection.Normalize();

                    // Avoid division by zero
                    RepulsionDirection *= (this->NeighbourRadius / FMath::Max(Distance, 1.0f));                 
                    SteeringForce += RepulsionDirection;
                }

                NeighbourCount++;
            }
        }
    }

    if (NeighbourCount > 0)
    {
        SteeringForce /= NeighbourCount;

        if (!SteeringForce.IsNearlyZero())
        {
            SteeringForce.Normalize();
            SteeringForce *= this->MaxSpeed;
            SteeringForce -= Boid.Velocity;
            SteeringForce = this->LimitVectorLength(SteeringForce, this->MaxForce);
        }
    }

    return SteeringForce;
}


FVector UBoidSubsystem::ApplyAlignment(const FBoid& Boid)
{
    FVector AverageVelocity = FVector::ZeroVector;
    int32 NeighbourCount = 0;

    for (const FBoid& OtherBoid : this->Boids)
    {
        if (OtherBoid.Id != Boid.Id)
        {
            float Distance = FVector::Distance(Boid.Position, OtherBoid.Position);

            if (Distance < this->NeighbourRadius)
            {
                AverageVelocity += OtherBoid.Velocity;
                NeighbourCount++;
            }
        }
    }

    if (NeighbourCount > 0)
    {
        AverageVelocity /= NeighbourCount;

        if (!AverageVelocity.IsNearlyZero())
        {
            AverageVelocity.Normalize();
            AverageVelocity *= this->MaxSpeed;

            FVector SteeringForce = AverageVelocity - Boid.Velocity;
            SteeringForce = this->LimitVectorLength(SteeringForce, this->MaxForce);
            return SteeringForce;
        }
    }

    return FVector::ZeroVector;
}


FVector UBoidSubsystem::ApplyCohesion(const FBoid& Boid)
{
    FVector CenterOfMass = FVector::ZeroVector;
    int32 NeighbourCount = 0;
    
    for (const FBoid& OtherBoid : this->Boids)
    {
        if (OtherBoid.Id != Boid.Id)
        {
            float Distance = FVector::Distance(Boid.Position, OtherBoid.Position);

            if (Distance < this->NeighbourRadius)
            {
                CenterOfMass += OtherBoid.Position;
                NeighbourCount++;
            }
        }
    }

    if (NeighbourCount > 0)
    {
        CenterOfMass /= NeighbourCount;

        FVector DesiredVelocity = CenterOfMass - Boid.Position;

        if (!DesiredVelocity.IsNearlyZero())
        {
            DesiredVelocity.Normalize();
            DesiredVelocity *= this->MaxSpeed;

            FVector SteeringForce = DesiredVelocity - Boid.Velocity;
            SteeringForce = this->LimitVectorLength(SteeringForce, this->MaxForce);
            return SteeringForce;
        }
    }   

    return FVector::ZeroVector;
}

FVector UBoidSubsystem::LimitVectorLength(const FVector& Vector, float MaxSize)
{
    if (Vector.SizeSquared() > FMath::Square(MaxSize))
    {
        return Vector.GetSafeNormal() * MaxSize;
    }
    return Vector;
}