#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "FoodDataStruct.generated.h"

USTRUCT(BlueprintType)
struct BADBOY_API FUFoodDataStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "FoodName", MakeStructureDefaultValue = "Taco"))
	FName FoodName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Mesh", MakeStructureDefaultValue = "/Script/Engine.StaticMesh'/Game/Art/Models/Food/Taco.Taco'"))
	TObjectPtr<UStaticMesh> Mesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "HealValue", MakeStructureDefaultValue = "2.000000"))
	double HealValue;


};
