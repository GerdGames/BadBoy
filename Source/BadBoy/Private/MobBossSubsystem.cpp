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

bool UMobBossSubsystem::LockTokens()
{
	if (locked == false)
	{
		attackTokenCount = 0;
		locked = true;
		return true;
	}
	//then mob boss must be already locked
	else 
	{
		return false;
	}
}

void UMobBossSubsystem::UnlockTokens()
{
	//return true to signal a successful unlock
	if (locked == true)
	{
		attackTokenCount = maxAttackTokens;
		locked = false;
	}
}

void UMobBossSubsystem::DelayedUnlock(float lockTime)
{
	GetWorld()->GetTimerManager().SetTimer(UnlockDelayTimer, this, &UMobBossSubsystem::UnlockTokens, lockTime, true);
}

bool UMobBossSubsystem::SetMaxTokens(int newMaxTokens)
{
	maxAttackTokens = newMaxTokens;
	return true;
}
