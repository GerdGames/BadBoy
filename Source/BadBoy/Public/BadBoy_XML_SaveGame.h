// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "XmlString.h"
#include "BadBoy_XML_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API UBadBoy_XML_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Cash"), Category = "SaveGame")
		void SetCash(float cash);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Cash"), Category = "SaveGame")
		float GetCash();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Health"), Category = "SaveGame")
		void SetHealth(float health);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Health"), Category = "SaveGame")
		float GetHealth();

private:
	FString GameDataXML;

	void XmlToString(const FXmlNode& Node, const FString& Indent, FString& Output);
	
};
