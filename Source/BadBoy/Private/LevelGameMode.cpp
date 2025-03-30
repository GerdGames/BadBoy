// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameMode.h"

void ALevelGameMode::startLevelScoring(int startRestoration)
{
	//start timer
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, 3600.0, false);

	//set starting restoration
	StartingRestoration = startRestoration;
}

void ALevelGameMode::endLevelScoring(int endRestoration)
{
	//stop timer
	GetWorld()->GetTimerManager().PauseTimer(LevelTimerHandle);

	//set ending restoration
	EndingRestoration = endRestoration;
}

int ALevelGameMode::getFoodWadGrowth()
{
	return EndingRestoration - StartingRestoration;
}
