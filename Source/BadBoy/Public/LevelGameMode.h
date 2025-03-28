// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API ALevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//timer for level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle LevelTimerHandle;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Level Scoring"), Category = "Score")
	void startLevelScoring();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "End Level Scoring"), Category = "Score")
	void endLevelScoring();
};
