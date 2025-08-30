// Fill out your copyright notice in the Description page of Project Settings.


#include "MobBossSubsystem.h"

bool UMobBossSubsystem::TryToTakeAttackToken()
{
	if (attackTokenCount > 0)
	{
		attackTokenCount--;
		UE_LOG(LogTemp, Warning, TEXT("Available Tokens: %d MaxTokens: %d"), attackTokenCount, maxAttackTokens);
		return true;
	}
	else
	{
		return false;
	}
}

bool UMobBossSubsystem::ReturnAttackToken()
{
	if (attackTokenCount >= maxAttackTokens)
	{
		attackTokenCount = maxAttackTokens;
		return false;
	}
	else
	{
		attackTokenCount++;
		UE_LOG(LogTemp, Warning, TEXT("Available Tokens: %d MaxTokens: %d"), attackTokenCount, maxAttackTokens);
		return true;
	}
}

bool UMobBossSubsystem::LockTokens()
{
	if (locked == false)
	{
		attackTokenCount = 0;
		locked = true;
		return true;
	}
	//then mob boss must be already locked
	else 
	{
		return false;
	}
}

void UMobBossSubsystem::UnlockTokens()
{
	//return true to signal a successful unlock
	if (locked == true)
	{
		attackTokenCount = maxAttackTokens;
		locked = false;
	}
}

void UMobBossSubsystem::DelayedUnlock(float lockTime)
{
	GetWorld()->GetTimerManager().SetTimer(UnlockDelayTimer, this, &UMobBossSubsystem::UnlockTokens, lockTime, true);
}

bool UMobBossSubsystem::SetMaxTokens(int newMaxTokens)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Max Tokens from: %d to %d"), maxAttackTokens, newMaxTokens);

	if (maxAttackTokens < newMaxTokens)
	{
		attackTokenCount += newMaxTokens - maxAttackTokens;
		UE_LOG(LogTemp, Warning, TEXT("Adding %d Tokens to available count"), (newMaxTokens - maxAttackTokens));
	}

	else if(maxAttackTokens > newMaxTokens){
		if (attackTokenCount > newMaxTokens)
		{
			attackTokenCount = newMaxTokens;
			UE_LOG(LogTemp, Warning, TEXT("Reducing Max Tokens to %d"), (newMaxTokens));
		}
	}

	maxAttackTokens = newMaxTokens;
	return true;
}

bool UMobBossSubsystem::addActorToRegistry(AActor* actor)
{
	for (AActor* entry : EnemyActors)
	{
		if (actor == entry)
		{
			return false;
		}
	}

	EnemyActors.Add(actor);

	return true;
}

bool UMobBossSubsystem::removeActorFromRegistry(AActor* actor)
{
	for (AActor* entry : EnemyActors)
	{
		if (actor == entry)
		{
			EnemyActors.Remove(entry);
		}
	}


	return false;
}

bool UMobBossSubsystem::checkForEnemyInRange(AActor* startActor, float range)
{
	for (AActor* entry : EnemyActors)
	{
		if (startActor == entry)
		{
			continue;
		}

		double distance = FVector::Distance(startActor->GetActorLocation(), entry->GetActorLocation());

		if (distance < range)
		{
			return true;
		}
	}

	return false;
}

FVector UMobBossSubsystem::getSeparationVectorFromEnemies(AActor* startActor, float separationRange)
{
	FVector separationVector(0, 0, 0);
	FVector runningVector(0, 0, 0);
	int enemyCount = 0;

	for (AActor* entry : EnemyActors)
	{
		if (startActor == entry)
		{
			continue;
		}

		double distance = FVector::Distance(startActor->GetActorLocation(), entry->GetActorLocation());

		if (distance < separationRange)
		{
			FVector dir = startActor->GetActorLocation() - entry->GetActorLocation();
			dir.Normalize();
			runningVector = runningVector + dir;
			enemyCount++;
		}
	}

	if (enemyCount == 0)
	{
		return separationVector;
	}
	else 
	{
		separationVector = runningVector / enemyCount;
		separationVector.Normalize();
		return separationVector;
	}
}


AActor* UMobBossSubsystem::getClosestEnemyInDirection(AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset)
{
	AActor* bestFit = nullptr;
	float bestDistance = 10000000;

	FVector searchStart = StartActor->GetActorLocation() + (startOffset * SearchDirection);

	for (AActor* actor : EnemyActors)
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
		}
	}

	return bestFit;
}