#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Datas/CustomDatas.h"
#include "CInventoryWidget.generated.h"

UCLASS()
class UE5_RPG_SERIES_API UCInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* ItemDataList;

private:
	TArray<FItemList*> Items;

//public:
//	UPROPERTY(meta = (BindWidget))
//	class UCanvasPanel* ItemSlot;
//
//	UPROPERTY(meta = (BindWidget))
//	class UHorizontalBox* ItemContainor;
//
//	UPROPERTY(meta = (BindWidget))
//	class UVerticalBox* InventoryContainor;

};
