#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Datas/CustomDatas.h"
#include "CInventoryWidget.generated.h"

UCLASS()
class UE5_RPG_SERIES_API UCInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	void CheckItem(int InItemNum = -1);
	void IncreaseItem(class UCItemWidget* InWidget, int InItemNum = -1);
	class UCItemWidget* AddItem(int InItemNum = -1);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* ItemDataList;

private:
	TArray<FItemList*> Items;

public:
	TArray<class UCanvasPanel*> ItemSlots;
	TArray<class UHorizontalBox*> ItemContainors;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* InventoryContainor;

	class AUE5_RPG_SeriesPlayerController* PlayerController;

	TSubclassOf<class UCItemWidget> ItemWidgetClass;
};
