// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Height_EnvQueryTest.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API UHeight_EnvQueryTest : public UEnvQueryTest
{
	GENERATED_BODY()

	UHeight_EnvQueryTest(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
	
};
