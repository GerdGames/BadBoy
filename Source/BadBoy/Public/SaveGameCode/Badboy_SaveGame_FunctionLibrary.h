// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <LevelCompletionStruct_C.h>
#include "Kismet/BlueprintFunctionLibrary.h"
#include <MoveUnlockStruct.h>
#include <Episode.h>
#include "Badboy_SaveGame_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API UBadboy_SaveGame_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Level Complete"), Category = "SaveGame")
		static FULevelCompletionStruct SetLevelComplete(bool completion, FULevelCompletionStruct LevelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Level Unlocked"), Category = "SaveGame")
		static FULevelCompletionStruct SetLevelUnlocked(bool completion, FULevelCompletionStruct LevelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Beefy Bar Eaten"), Category = "SaveGame")
		static FULevelCompletionStruct SetBarEaten(bool completion, FULevelCompletionStruct LevelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Move Unlocked"), Category = "SaveGame")
		static FUMoveUnlockStruct SetMoveUnlocked(bool completion, FUMoveUnlockStruct MoveStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find Level in Episode"), Category = "SaveGame")
		static bool FindLevelInEpisode(FString LevelName, FUEpisode Episode, FULevelCompletionStruct& LevelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find Level in List of Episodes"), Category = "SaveGame")
		static bool FindLevelInListOfEpisodes(FString LevelName, TMap<FString, FUEpisode> Episodes, FString& EpisodeName, FULevelCompletionStruct& LevelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Update Level in List of Episodes"), Category = "SaveGame")
		static bool UpdateLevelInListOfEpisodes(FString LevelName, TMap<FString, FUEpisode> Episodes, TMap<FString, FUEpisode>& EpisodesUpdated, bool Completed, bool Unlocked, bool BeefyBarEaten);
};