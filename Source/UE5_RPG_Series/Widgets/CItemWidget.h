#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CItemWidget.generated.h"

UCLASS()
class UE5_RPG_SERIES_API UCItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	void SetImageTexture(class UTexture2D* InTexture);
	void IncreaseItemCount();
	void DecreaseItemCount();

	FORCEINLINE void SetItemNum(int InNum) { ItemNum = InNum; }
	FORCEINLINE int GetItemNum() { return ItemNum; }

	class UObject* GetImageTexture();

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

private:
	int ItemNum = -1;
	int Count = 0;
};
