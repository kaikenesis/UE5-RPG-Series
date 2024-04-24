#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CustomDatas.generated.h"

USTRUCT(BlueprintType)
struct FItemList : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 ItemNum;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UTexture2D* ItemTexture;
};

UCLASS()
class UE5_RPG_SERIES_API ACustomDatas : public AActor
{
	GENERATED_BODY()
};
