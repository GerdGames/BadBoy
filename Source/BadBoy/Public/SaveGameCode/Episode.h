// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include <LevelCompletionStruct_C.h>
#include "Episode.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct BADBOY_API FUEpisode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool levelComplete = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FULevelCompletionStruct> Levels;
};
