// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "XmlString.h"
#include <MoveUnlockStruct.h>
#include <LevelCompletionStruct_C.h>
#include <Episode.h>
#include "BadBoy_XML_SaveGame.generated.h"


/**
 * 
 */
UCLASS()
class BADBOY_API UBadBoy_XML_SaveGame : public USaveGame
{
	GENERATED_BODY()

	UBadBoy_XML_SaveGame();
	UBadBoy_XML_SaveGame(float cash, float health);

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Cash"), Category = "SaveGame")
		void SetCash(float cash);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Cash"), Category = "SaveGame")
		float GetCash();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Health"), Category = "SaveGame")
		void SetHealth(float health);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Health"), Category = "SaveGame")
		float GetHealth();

	//Moves
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Move"), Category = "SaveGame")
		void SetMove(FString moveName, FUMoveUnlockStruct moveStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Move"), Category = "SaveGame")
		FUMoveUnlockStruct GetMove(FString moveName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Moves"), Category = "SaveGame")
		void SetMoves(TMap<FString, FUMoveUnlockStruct> moves);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Moves"), Category = "SaveGame")
		TMap<FString, FUMoveUnlockStruct> GetMoves();

	//Episodes
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Level"), Category = "SaveGame")
		void SetLevel(FString levelName, FString episodeName, FULevelCompletionStruct levelStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Level"), Category = "SaveGame")
		FULevelCompletionStruct GetLevel(FString levelName, FString episodeName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Episode"), Category = "SaveGame")
		void SetEpisode(FString episodeName, FUEpisode episodeStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Episode"), Category = "SaveGame")
		FUEpisode GetEpisode(FString episodeName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Episodes"), Category = "SaveGame")
		void SetEpisodes(TMap< FString, FUEpisode> episodesStruct);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Episodes"), Category = "SaveGame")
		TMap< FString, FUEpisode> GetEpisodes();



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GameDataXML = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <SAVE_GAME>\n </SAVE_GAME>") LINE_TERMINATOR;

private:
	
	const FString XmlHeader = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	void XmlToString(const FXmlNode& Node, const FString& Indent, FString& Output);

	FXmlNode* TryGetChildNode(FXmlNode* Node, const FString& nodeName);
	FXmlNode* TryGetChildNode(FXmlNode* Node, const FString& nodeName, const FString& defaultValue );
	
};
