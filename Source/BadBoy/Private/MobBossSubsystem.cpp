// Fill out your copyright notice in the Description page of Project Settings.


#include "MobBossSubsystem.h"

bool UMobBossSubsystem::TryToTakeAttackToken()
{
	if (attackTokenCount > 0)
	{
		attackTokenCount--;
		return true;
	}
	else
	{
		return false;
	}
}

bool UMobBossSubsystem::ReturnAttackToken()
{
	if (attackTokenCount >= maxAttackTokens)
	{
		attackTokenCount = maxAttackTokens;
		return false;
	}
	else 
	{
		attackTokenCount++;
		return true;
	}
}
