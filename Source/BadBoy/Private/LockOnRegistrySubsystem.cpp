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

AActor* ULockOnRegistrySubsystem::getClosestTargetInDirection(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{
	AActor* bestFit = nullptr;
	float bestAngle = 360;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	TArray<AActor*> viableTargets = getViableLockOnTargets(PlayerActor->GetActorLocation(), maxDistance);

	for (AActor* actor : viableTargets)
	{
		if (actor != StartActor && actor != PlayerActor)
		{
			//get vector between the current target and the next one, to ensure it's in the correct dir
			FVector VectorToActor = (actor->GetActorLocation() - StartActor->GetActorLocation());
			VectorToActor.Normalize();

			float angle = getAngleDifferenceBetween2Vectors(VectorToActor, SearchDirection);

			if (true)//angle <= angleTolerance)
			{
				//get vector from player to current target
				FVector VectorPlayerToTarget = (StartActor->GetActorLocation() - PlayerActor->GetActorLocation());
				VectorPlayerToTarget.Normalize();

				//get vector from player to potential target
				FVector VectorPlayerToCandidate = (actor->GetActorLocation() - PlayerActor->GetActorLocation());
				VectorPlayerToCandidate.Normalize();

				//get the difference between them
				float targetDiffAngle = getAngleDifferenceBetween2Vectors(VectorPlayerToTarget, VectorPlayerToCandidate);
				//UE_LOG(LogTemp, Warning, TEXT("Angle Difference: %f"), targetDiffAngle);

				if (targetDiffAngle < bestAngle)
				{
					bestAngle = targetDiffAngle;
					bestFit = actor;

					//UE_LOG(LogTemp, Warning, TEXT("Selected Actor: %s"), TCHAR_TO_UTF8(*actor->GetName()));
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

// Prioritizes enemies within angle and range
// if one is not found, go for the closest enemy in range
// if none found in range, don't target anything
AActor* ULockOnRegistrySubsystem::getEnemyForSoftLock(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{

	AActor* bestFit = nullptr;
	AActor* outOfAngleFit = nullptr;
	float bestDistance = 10000000;
	float outOfAngleDistance = 10000000;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	TArray<AActor*> viableTargets = getViableLockOnTargets(PlayerActor->GetActorLocation(), maxDistance);

	for (AActor* actor : viableTargets)
	{
		if (actor != StartActor)
		{
			FVector VectorToActor = (actor->GetActorLocation() - searchStart);
			VectorToActor.Normalize();

			float angle = FMath::RadiansToDegrees(FMath::Acos(VectorToActor | SearchDirection));

			if (angle <= angleTolerance)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (distance < bestDistance)
				{
					bestDistance = distance;
					bestFit = actor;
				}
			}
			// if there isn't a fit in the angle yet
			else if (bestFit == nullptr)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (distance < outOfAngleDistance)
				{
					outOfAngleDistance = distance;
					outOfAngleFit = actor;
				}
			}
		}
	}

	if (bestFit == nullptr)
	{
		if (outOfAngleFit == nullptr)
		{
			return nullptr;
		}
		else
		{
			return outOfAngleFit;
		}
	}
	else
	{
		return bestFit;
	}
}

// Prioritizes enemies within angle and range
// if one is not found, go for the closest enemy 
// always target something as long as there is something to target
AActor* ULockOnRegistrySubsystem::getEnemyForHardLock(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{
	AActor* bestFit = nullptr;
	AActor* outOfAngleFit = nullptr;
	float bestDistance = 10000000;
	float outOfAngleDistance = 10000000;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	TArray<AActor*> viableTargets = getViableLockOnTargets(PlayerActor->GetActorLocation(), maxDistance);

	for (AActor* actor : viableTargets)
	{
		if (actor != StartActor)
		{
			FVector VectorToActor = (actor->GetActorLocation() - searchStart);
			VectorToActor.Normalize();

			float angle = FMath::RadiansToDegrees(FMath::Acos(VectorToActor | SearchDirection));

			if (angle <= angleTolerance)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (distance < bestDistance)
				{
					bestDistance = distance;
					bestFit = actor;
				}
			}
			// if there isn't a fit in the angle yet
			else if (bestFit == nullptr)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (distance < outOfAngleDistance)
				{
					outOfAngleDistance = distance;
					outOfAngleFit = actor;
				}
			}
		}
	}

	if (bestFit == nullptr)
	{
		if (outOfAngleFit == nullptr)
		{
			if (viableTargets.Num() <= 0)
			{
				return nullptr;
			}
			else
			{
				return viableTargets[0];
			}
		}
		else
		{
			return outOfAngleFit;
		}
	}
	else
	{
		return bestFit;
	}
}

// Get first enemy in a direction
// prioritize small movement in a direction
// If no enemy in direction, get the closest enemy
// Distance shouldn't matter much
AActor* ULockOnRegistrySubsystem::getEnemyForChangeTarget(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{
	AActor* bestFit = nullptr;
	AActor* outOfAngleFit = nullptr;
	float bestAngle = 360;
	float outOfAngleAngle = 360;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	TArray<AActor*> viableTargets = getViableLockOnTargets(PlayerActor->GetActorLocation(), maxDistance);

	for (AActor* actor : viableTargets)
	{
		if (actor != StartActor)
		{
			//get vector between the current target and the next one, to ensure it's in the correct dir
			FVector VectorToActor = (actor->GetActorLocation() - StartActor->GetActorLocation());
			VectorToActor.Normalize();

			//difference between the vector to the actor, and the search direction
			float angle = getAngleDifferenceBetween2Vectors(VectorToActor, SearchDirection);

			//get vector from player to current target
			FVector VectorPlayerToTarget = (StartActor->GetActorLocation() - PlayerActor->GetActorLocation());
			VectorPlayerToTarget.Normalize();

			//get vector from player to potential target
			FVector VectorPlayerToCandidate = (actor->GetActorLocation() - PlayerActor->GetActorLocation());
			VectorPlayerToCandidate.Normalize();

			//get the difference between them
			float targetDiffAngle = getAngleDifferenceBetween2Vectors(VectorPlayerToTarget, VectorPlayerToCandidate);
			//UE_LOG(LogTemp, Warning, TEXT("Angle Difference: %f"), targetDiffAngle);

			if (angle <= angleTolerance)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (targetDiffAngle < bestAngle)
				{
					bestAngle = targetDiffAngle;
					bestFit = actor;
				}
			}
			// if there isn't a fit in the angle yet
			else if (bestFit == nullptr)
			{
				double distance = FVector::Distance(searchStart, actor->GetActorLocation());

				if (targetDiffAngle < outOfAngleAngle)
				{
					bestAngle = targetDiffAngle;
					outOfAngleFit = actor;
				}
			}
		}
	}

	if (bestFit == nullptr)
	{
		if (outOfAngleFit == nullptr)
		{
			if (viableTargets.Num() <= 0)
			{
				return nullptr;
			}
			else
			{
				return viableTargets[0];
			}
		}
		else
		{
			return outOfAngleFit;
		}
	}
	else
	{
		return bestFit;
	}
}