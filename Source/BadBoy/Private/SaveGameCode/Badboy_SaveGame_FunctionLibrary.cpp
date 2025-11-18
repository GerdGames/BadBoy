// Fill out your copyright notice in the Description page of Project Settings.
#include <SaveGameCode/Badboy_SaveGame_FunctionLibrary.h>


FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetLevelComplete(bool completion, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.levelComplete = completion;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetLevelUnlocked(bool completion, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.levelUnlocked = completion;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetBarEaten(bool completion, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.beefyBarEaten = completion;
	return LevelStruct;
}

FUMoveUnlockStruct UBadboy_SaveGame_FunctionLibrary::SetMoveUnlocked(bool completion, FUMoveUnlockStruct MoveStruct)
{
	MoveStruct.unlocked = completion;
	return MoveStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetRecordFoodWad(TArray<FName> recordWad, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.recordFoodwad = recordWad;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetRecordWadGrowth(float recordWadGrowth, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.recordWadGrowth = recordWadGrowth;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetRecordHanger(float recordHanger, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.recordHanger = recordHanger;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetRecordTime(float recordTime, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.recordTime = recordTime;
	return LevelStruct;
}

FULevelCompletionStruct UBadboy_SaveGame_FunctionLibrary::SetCollectables(int collectables, FULevelCompletionStruct LevelStruct)
{
	LevelStruct.collectables = collectables;
	return LevelStruct;
}

bool UBadboy_SaveGame_FunctionLibrary::FindLevelInEpisode(FString LevelName, FUEpisode Episode, FULevelCompletionStruct& LevelStruct)
{
	if (Episode.Levels.Contains(LevelName))
	{
		LevelStruct = Episode.Levels[LevelName];
		return true;
	}
	else
		return false;
}

bool UBadboy_SaveGame_FunctionLibrary::FindLevelInListOfEpisodes(FString LevelName, TMap<FString, FUEpisode> Episodes, FString& EpisodeName, FULevelCompletionStruct& LevelStruct)
{
	bool findResult = false;

	for (auto& ep : Episodes)
	{
		findResult = FindLevelInEpisode(LevelName, ep.Value, LevelStruct);

		if (findResult)
		{
			EpisodeName = *ep.Key;
			return true;
		}
	}

	return false;
}

bool UBadboy_SaveGame_FunctionLibrary::CheckToUseNewFoodWad(TArray<FName> currentWad, TArray<FName> newWad)
{
	/*if (currentWad.IsEmpty()) {
		return true;
	}

	int currentWadHP = 0;
	int newWadHP = 0;

	for (FUFoodDataStruct foodItem : currentWad) 
	{
		currentWadHP += foodItem.HealValue;
	}

	for (FUFoodDataStruct foodItem : newWad)
	{
		newWadHP += foodItem.HealValue;
	}

	if (newWadHP > currentWadHP) {
		return true;
	}
	else {
		return false;
	}*/

	return true;
}

bool UBadboy_SaveGame_FunctionLibrary::UpdateLevelInListOfEpisodes(FString LevelName, TMap<FString, FUEpisode> Episodes, TMap<FString, FUEpisode>& EpisodesUpdated, bool Completed, bool Unlocked, bool BeefyBarEaten, TArray<FName> recordWad, float recordWadGrowth, float recordHanger, float recordTime, int recordCollectableCount)
{
	//first find the level
	FULevelCompletionStruct lvlStr;
	FString epName;

	bool findResult = FindLevelInListOfEpisodes(LevelName, Episodes, epName, lvlStr);

	if (findResult)
	{
		//set completion on the level struct
		if (Completed)
			lvlStr = SetLevelComplete(true, lvlStr);

		if (Unlocked)
			lvlStr = SetLevelUnlocked(true, lvlStr);

		if (BeefyBarEaten)
			lvlStr = SetBarEaten(true, lvlStr);

		if(CheckToUseNewFoodWad(lvlStr.recordFoodwad, recordWad))
			lvlStr = SetRecordFoodWad(recordWad, lvlStr);

		if (recordHanger > lvlStr.recordHanger)
			lvlStr = SetRecordHanger(recordHanger, lvlStr);

		if (recordWadGrowth > lvlStr.recordWadGrowth)
			lvlStr = SetRecordWadGrowth(recordWadGrowth, lvlStr);

		if (recordTime < lvlStr.recordTime || lvlStr.recordTime == 0.0f)
			lvlStr = SetRecordTime(recordTime, lvlStr);

		if (recordCollectableCount > lvlStr.collectables)
			lvlStr = SetCollectables(recordCollectableCount, lvlStr);

		//update the episode
		FUEpisode tempEp = Episodes[epName];
		tempEp.Levels.Add(LevelName, lvlStr);

		//Update the list of episodes
		EpisodesUpdated = Episodes;
		EpisodesUpdated.Add(epName, tempEp);

		return true;
	}

	return false;
}


