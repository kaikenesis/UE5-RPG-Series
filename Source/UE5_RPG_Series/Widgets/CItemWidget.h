#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemSlotClickedSignature, class UCItemWidget*, InItemWidget);

UCLASS()
class UE5_RPG_SERIES_API UCItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	void Init();

	void SetImageTexture(class UTexture2D* InTexture);
	void SetItemCount(int InValue);
	void IncreaseItemCount(int InValue);
	void DecreaseItemCount(int InValue);

	void SetVisibleWithCount(ESlateVisibility InVisibility);
	// Count Visibilty = Hidden
	void SetVisibleWithoutCount(ESlateVisibility InVisibility);

	void BindItemSlotButton();

	FORCEINLINE void SetItemNum(int InNum) { ItemNum = InNum; }
	FORCEINLINE int GetItemNum() { return ItemNum; }
	FORCEINLINE int GetItemCount() { return Count; }

	class UObject* GetImageTexture();

public:
	UFUNCTION()
	void OnClicked();

public:
	FItemSlotClickedSignature OnItemSlotClicked;

public:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

private:
	int ItemNum = 1;
	int Count = 0;
};
