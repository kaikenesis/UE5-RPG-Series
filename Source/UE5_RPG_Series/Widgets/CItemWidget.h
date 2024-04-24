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
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
};
