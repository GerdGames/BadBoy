// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LockOnRegistrySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BADBOY_API ULockOnRegistrySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:

	struct LockOnEntry {
		bool priority;
		AActor* actor;
	};
	TArray<LockOnEntry*> LockOnActors;


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Actor to Lock On Registry"), Category = "Lock On")
	bool addActorToRegistry(AActor* actor, bool priority);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove Actor from Lock On Registry"), Category = "Lock On")
	bool removeActorFromRegistry(AActor* actor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Update Actor Priority"), Category = "Lock On")
	bool updateActorPriority(AActor* actor, bool priority);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Closest LockOn Target"), Category = "Lock On")
	AActor* getClosestTarget(AActor* StartActor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Next LockOn Target In Direction"), Category = "Lock On")
	AActor* getNextTargetInDirection(AActor* StartActor, FVector SearchDirection);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Closest LockOn Target In Direction"), Category = "Lock On")
	AActor* getClosestTargetInDirection(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Viable LockOn Targets"), Category = "Lock On")
	TArray<AActor*> getViableLockOnTargets(FVector searchStart, float maxDistance);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Priority LockOn Targets"), Category = "Lock On")
	TArray<AActor*> getPriorityTargets();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Enemy For Soft Lock"), Category = "Lock On")
	AActor* getEnemyForSoftLock(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Enemy For Hard Lock"), Category = "Lock On")
	AActor* getEnemyForHardLock(AActor* PlayerActor, AActor* StartActor, FVector SearchDirection, float maxDistance, float angleTolerance, float startOffset);

	float getAngleDifferenceBetween2Vectors(FVector vector1, FVector vector2);
};
