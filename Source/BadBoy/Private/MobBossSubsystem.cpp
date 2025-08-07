// Fill out your copyright notice in the Description page of Project Settings.


#include "MobBossSubsystem.h"

bool UMobBossSubsystem::TryToTakeAttackToken()
{
	if (attackTokenCount > 0)
	{
		attackTokenCount--;
		UE_LOG(LogTemp, Warning, TEXT("Available Tokens: %d MaxTokens: %d"), attackTokenCount, maxAttackTokens);
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
		UE_LOG(LogTemp, Warning, TEXT("Available Tokens: %d MaxTokens: %d"), attackTokenCount, maxAttackTokens);
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
	UE_LOG(LogTemp, Warning, TEXT("Updating Max Tokens from: %d to %d"), maxAttackTokens, newMaxTokens);

	if (maxAttackTokens < newMaxTokens)
	{
		attackTokenCount += newMaxTokens - maxAttackTokens;
		UE_LOG(LogTemp, Warning, TEXT("Adding %d Tokens to available count"), (newMaxTokens - maxAttackTokens));
	}

	else if(maxAttackTokens > newMaxTokens){
		if (attackTokenCount > newMaxTokens)
		{
			attackTokenCount = newMaxTokens;
			UE_LOG(LogTemp, Warning, TEXT("Reducing Max Tokens to %d"), (newMaxTokens));
		}
	}

	maxAttackTokens = newMaxTokens;
	return true;
}
