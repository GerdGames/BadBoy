// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameMode.h"

void ALevelGameMode::startLevelScoring()
{
	//start timer
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, 3600.0, false);
}

void ALevelGameMode::endLevelScoring()
{
	//stop timer
	GetWorld()->GetTimerManager().PauseTimer(LevelTimerHandle);
}
