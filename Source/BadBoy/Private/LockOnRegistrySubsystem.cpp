// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnRegistrySubsystem.h"

bool ULockOnRegistrySubsystem::addActorToRegistry(AActor* actor, bool priority)
{
	for (LockOnEntry* entry : LockOnActors)
	{
		//AActor* entryActor = entry->actor;
		if (actor == entry->actor)
		{
			return false;
		}
	}

	LockOnEntry* newEntry = new LockOnEntry();
	newEntry->actor = actor;
	newEntry->priority = priority;

	LockOnActors.Add(newEntry);

	return true;
}

bool ULockOnRegistrySubsystem::removeActorFromRegistry(AActor* actor)
{
	for (LockOnEntry* entry : LockOnActors)
	{
		//AActor* entryActor = entry->actor;
		if (actor == entry->actor)
		{
			LockOnActors.Remove(entry);
			
			return true;
		}
	}
	

	return false;
}

bool ULockOnRegistrySubsystem::updateActorPriority(AActor* actor, bool priority)
{
	for (LockOnEntry* entry : LockOnActors)
	{
		//AActor* entryActor = entry->actor;
		if (actor == entry->actor)
		{
			entry->priority = priority;

			return true;
		}
	}


	return false;
}

AActor* ULockOnRegistrySubsystem::getClosestTarget(AActor* StartActor)
{
	AActor* bestFit = nullptr;
	float bestDistance = 10000000;

	TArray<AActor*> viableTargets = getViableLockOnTargets(StartActor->GetActorLocation(), 10000);

	for (AActor* actor : viableTargets)
	{
		double distance = FVector::Distance(StartActor->GetActorLocation(), actor->GetActorLocation());

		if (distance < bestDistance)
		{
			bestDistance = distance;
			bestFit = actor;
		}
	}

	return bestFit;
}

AActor* ULockOnRegistrySubsystem::getNextTargetInDirection(AActor* StartActor, FVector SearchDirection)
{
	AActor* bestFit = nullptr;
	float bestAngle = 360;

	TArray<AActor*> viableTargets = getViableLockOnTargets(StartActor->GetActorLocation(), 10000);

	for (AActor* actor : viableTargets)
	{
		FVector VectorToActor = (StartActor->GetActorLocation() - actor->GetActorLocation());
		VectorToActor.Normalize();

		float angle = getAngleDifferenceBetween2Vectors(VectorToActor, SearchDirection);

		if (angle < bestAngle)
		{
			bestAngle = angle;
			bestFit = actor;
		}
	}

	return bestFit;
}

AActor* ULockOnRegistrySubsystem::getClosestTargetInDirection(AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{
	AActor* bestFit = nullptr;
	float bestDistance = 10000000;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	TArray<AActor*> viableTargets = getViableLockOnTargets(StartActor->GetActorLocation(), maxDistance);

	for (AActor* actor : viableTargets)
	{
		if (actor != StartActor)
		{
			FVector VectorToActor = (actor->GetActorLocation() - searchStart);
			VectorToActor.Normalize();

			float angle = getAngleDifferenceBetween2Vectors(VectorToActor, SearchDirection);

			if (angle <= angleTolerance)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (distance < bestDistance)
				{
					bestDistance = distance;
					bestFit = actor;
				}
			}
		}
	}

	return bestFit;
}

TArray<AActor*> ULockOnRegistrySubsystem::getViableLockOnTargets(FVector searchStart, float maxDistance)
{
	TArray<AActor*> ViableTargets = TArray<AActor*>();


	for (LockOnEntry* entry : LockOnActors)
	{
		if (entry->priority)
		{
			ViableTargets.Add(entry->actor);
		}

		else
		{
			AActor* candidate = entry->actor;

			if (candidate->IsValidLowLevel())
			{
				double distance = FVector::Distance(searchStart, candidate->GetActorLocation());

				if (distance <= maxDistance)
				{
					FHitResult result;
					GetWorld()->LineTraceSingleByObjectType(result, searchStart, candidate->GetActorLocation(), FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)));

					//if there were no blocks in the line trace
					if (!result.bBlockingHit)
					{
						ViableTargets.Add(candidate);
					}
				}
			}
		}
	}

	return ViableTargets;
}


TArray<AActor*> ULockOnRegistrySubsystem::getPriorityTargets()
{
	TArray<AActor*> PriorityTargets = TArray<AActor*>();

	for (LockOnEntry* entry : LockOnActors)
	{
		if (entry->priority)
		{
			PriorityTargets.Add(entry->actor);
		}
	}

	return PriorityTargets;
}

float ULockOnRegistrySubsystem::getAngleDifferenceBetween2Vectors(FVector vector1, FVector vector2)
{
	return FMath::RadiansToDegrees(FMath::Acos(vector1 | vector2));
}
