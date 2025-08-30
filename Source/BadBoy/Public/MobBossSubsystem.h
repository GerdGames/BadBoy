// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/GameplayStatics.h>
#include "Subsystems/WorldSubsystem.h"
#include "MobBossSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API UMobBossSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	int attackTokenCount = 1;
	int maxAttackTokens = 1;
	bool locked = false;
	TArray<AActor*> EnemyActors;

	FTimerHandle UnlockDelayTimer;

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Try To Take Attack Token"), Category = "Attack Token")
	bool TryToTakeAttackToken();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Return Attack Token"), Category = "Attack Token")
	bool ReturnAttackToken();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Lock Attack Tokens"), Category = "Attack Token")
	bool LockTokens();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Unlock Attack Tokens"), Category = "Attack Token")
	void UnlockTokens();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delayed Unlock"), Category = "Attack Token")
	void DelayedUnlock(float lockTime);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Max Attack Tokens"), Category = "Attack Token")
	bool SetMaxTokens(int newMaxTokens);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Actor to Enemy Registry"), Category = "Enemy Management")
	bool addActorToRegistry(AActor* actor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove Actor from Enemy Registry"), Category = "Enemy Management")
	bool removeActorFromRegistry(AActor* actor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Check For Enemy In Range"), Category = "Enemy Management")
	bool checkForEnemyInRange(AActor* startActor, float range);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Separation Vector From Enemies"), Category = "Enemy Management")
	FVector getSeparationVectorFromEnemies(AActor* startActor, float separationRange);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Closest Enemy In Direction"), Category = "Lock On")
	AActor* getClosestEnemyInDirection(AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset);
};
