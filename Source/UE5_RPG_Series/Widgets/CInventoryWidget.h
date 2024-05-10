#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Datas/CustomDatas.h"
#include "CInventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseInventoryClickedSignature);

UCLASS()
class UE5_RPG_SERIES_API UCInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void CheckItem(bool bUseItem, int InItemNum, int InItemValue);

	void IncreaseItem(class UCItemWidget* InWidget, int InItemValue);
	void DecreaseItem(class UCItemWidget* InWidget, int InItemValue);

	void AddItem(class UCItemWidget* InWidget, int InItemNum, int InItemValue);
	void RemoveItem(class UCItemWidget* InWidget);
	void OnClosedInventory();
	void LastMovedItemSlot(UCItemWidget* InItemWidget);

	void SetMouseItemPosition(FVector2D InPosition);

public:
	UFUNCTION()
	void OnItemSlotClicked(class UCItemWidget* InItemWidget);

	UFUNCTION()
	void HideWidget();

public:
	FCloseInventoryClickedSignature OnCloseInventoryClicked;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* ItemDataList;

private:
	TArray<FItemList*> Items;
	class UCItemWidget* MouseItem;
	class UCItemWidget* LastItemSlot;

public:
	TArray<class UCanvasPanel*> ItemSlots;
	TArray<class UHorizontalBox*> ItemContainors;
	TArray<class UBorder*> Borders;
	TArray<class UCItemWidget*> ItemWidgets;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* InventoryContainor;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;

	class AUE5_RPG_SeriesPlayerController* PlayerController;

	TSubclassOf<class UCItemWidget> ItemWidgetClass;
};
