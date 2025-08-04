// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Try To Take Attack Token"), Category = "Attack Token")
	bool TryToTakeAttackToken();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Return Attack Token"), Category = "Attack Token")
	bool ReturnAttackToken();
	
};
