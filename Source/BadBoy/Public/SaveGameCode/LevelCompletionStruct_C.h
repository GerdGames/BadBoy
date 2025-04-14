// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include <FoodDataStruct.h>
#include "LevelCompletionStruct_C.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BADBOY_API FULevelCompletionStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool levelComplete = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool levelUnlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool beefyBarEaten = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> recordFoodwad = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float recordWadGrowth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float recordHanger = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float recordTime = 0;
};
