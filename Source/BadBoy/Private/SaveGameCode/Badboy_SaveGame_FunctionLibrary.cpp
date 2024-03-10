// Fill out your copyright notice in the Description page of Project Settings.


#include "Badboy_SaveGame_FunctionLibrary.h"


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

bool UBadboy_SaveGame_FunctionLibrary::UpdateLevelInListOfEpisodes(FString LevelName, TMap<FString, FUEpisode> Episodes, TMap<FString, FUEpisode>& EpisodesUpdated, bool Completed, bool Unlocked, bool BeefyBarEaten)
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


