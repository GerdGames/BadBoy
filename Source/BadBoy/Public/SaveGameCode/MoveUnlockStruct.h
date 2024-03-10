// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "MoveUnlockStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BADBOY_API FUMoveUnlockStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool unlocked = false;
};
