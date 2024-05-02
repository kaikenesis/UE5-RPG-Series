#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInventory.generated.h"

UINTERFACE(MinimalAPI)
class UIInventory : public UInterface
{
	GENERATED_BODY()
};

class UE5_RPG_SERIES_API IIInventory
{
	GENERATED_BODY()

public:
	virtual void UseItem_Interface(int InItemNum, int InItemValue) = 0;
};
