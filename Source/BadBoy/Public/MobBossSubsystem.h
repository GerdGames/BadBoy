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
	int attackTokenCount = 2;
	int maxAttackTokens = 2;
	bool locked = false;

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
	
};
