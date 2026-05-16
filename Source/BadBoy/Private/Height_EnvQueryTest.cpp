// Fill out your copyright notice in the Description page of Project Settings.


#include "Height_EnvQueryTest.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"



UHeight_EnvQueryTest::UHeight_EnvQueryTest(const FObjectInitializer& ObjectInitializer)
{
	Cost = EEnvTestCost::Low;

	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();

}

void UHeight_EnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());

		AActor* Querier = (AActor *) QueryInstance.Owner.Get();

		float HeightDiff = ItemLocation.Z - (Querier->GetActorLocation().Z);

		UE_LOG(LogTemp, Warning, TEXT("Item Height: %d Querier Height: %d HeightDiff: %d"), ItemLocation.Z, Querier->GetActorLocation().Z, HeightDiff);

		It.SetScore(TestPurpose, FilterType, HeightDiff, -1000, 1000);
	}
}

FText UHeight_EnvQueryTest::GetDescriptionTitle() const
{
	return FText::FromString("Height Test");
}

FText UHeight_EnvQueryTest::GetDescriptionDetails() const
{
	return FText::FromString("Scores highest items");
}
