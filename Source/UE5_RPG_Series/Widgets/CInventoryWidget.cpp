#include "Widgets/CInventoryWidget.h"
#include "Engine/DataTable.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Widgets/CItemWidget.h"
#include "UE5_RPG_SeriesPlayerController.h"

UCInventoryWidget::UCInventoryWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UCItemWidget> widgetClass(TEXT("/Game/TopDown/Blueprints/WB_ItemSegment"));
	if (widgetClass.Succeeded())
		ItemWidgetClass = widgetClass.Class;
}

void UCInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnExit->OnClicked.AddDynamic(this, &UCInventoryWidget::HideWidget);

	AUE5_RPG_SeriesPlayerController* playerController = Cast<AUE5_RPG_SeriesPlayerController>(GetOwningPlayer());
	if(playerController != nullptr)
		PlayerController = playerController;

	ItemDataList->GetAllRows<FItemList>("", Items);

	TArray<UWidget*> inventoryChildren = InventoryContainor->GetAllChildren();
	for (const auto& child : inventoryChildren)
	{
		UHorizontalBox* itemContainor = Cast<UHorizontalBox>(child);
		if (itemContainor != nullptr)
		{
			ItemContainors.Add(itemContainor);
		}
	}

	for (const auto& itemContainor : ItemContainors)
	{
		TArray<UWidget*> containorChildren = itemContainor->GetAllChildren();
		for (const auto& child : containorChildren)
		{
			UCanvasPanel* itemSlot = Cast<UCanvasPanel>(child);
			if (itemSlot != nullptr)
				ItemSlots.Add(itemSlot);
		}
	}

	for (const auto& itemSlot : ItemSlots)
	{
		TArray<UWidget*> itemSlotChildren = itemSlot->GetAllChildren();
		for (const auto& child : itemSlotChildren)
		{
			UBorder* border = Cast<UBorder>(child);
			if (border != nullptr)
				Borders.Add(border);
		}
	}

	for (const auto& border : Borders)
	{
		TArray<UWidget*> borderChildren = border->GetAllChildren();
		for (const auto& child : borderChildren)
		{
			UCItemWidget* itemWidget = Cast<UCItemWidget>(child);
			if (itemWidget != nullptr)
			{
				itemWidget->Init();
				itemWidget->BindItemSlotButton();
				itemWidget->OnItemSlotClicked.AddDynamic(this, &UCInventoryWidget::OnItemSlotClicked);
				ItemWidgets.Add(itemWidget);
			}
		}
	}
	MouseItem->Init();
}

void UCInventoryWidget::CheckItem(bool bUseItem, int InItemNum, int InItemValue)
{
	for (const auto& itemWidget : ItemWidgets)
	{
		if (itemWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			if (itemWidget->GetItemNum() == Items[InItemNum]->ItemNum)
			{
				if (bUseItem == false)
				{
					IncreaseItem(itemWidget, InItemValue);
					return;
				}
				else
				{
					DecreaseItem(itemWidget, InItemValue);
					return;
				}
			}
		}
	}

	for (const auto& itemWidget : ItemWidgets)
	{
		if (itemWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			if (bUseItem == false)
			{
				AddItem(itemWidget, InItemNum, InItemValue);
				return;
			}
		}	
	}
}

void UCInventoryWidget::IncreaseItem(UCItemWidget* InWidget, int InItemValue)
{
	if (InWidget != nullptr)
		InWidget->IncreaseItemCount(InItemValue);
}

void UCInventoryWidget::DecreaseItem(UCItemWidget* InWidget, int InItemValue)
{
	if (InWidget != nullptr)
	{
		InWidget->DecreaseItemCount(InItemValue);

		if (InWidget->GetItemCount() == 0)
			RemoveItem(InWidget);
	}
}

void UCInventoryWidget::AddItem(class UCItemWidget* InWidget, int InItemNum, int InItemValue)
{
	if (InWidget != nullptr)
	{
		InWidget->SetImageTexture(Items[InItemNum]->ItemTexture);
		InWidget->IncreaseItemCount(InItemValue);
		InWidget->SetItemNum(InItemNum);

		InWidget->SetVisibleWithCount(ESlateVisibility::Visible);
	}

	return;
}

void UCInventoryWidget::RemoveItem(UCItemWidget* InWidget)
{
	if (InWidget != nullptr)
	{
		InWidget->SetVisibleWithCount(ESlateVisibility::Hidden);
	}
}

void UCInventoryWidget::SetMouseItemPosition(FVector2D InPosition)
{
	MouseItem->SetPositionInViewport(InPosition);
}

void UCInventoryWidget::HideWidget()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("HideWidget"));

	FInputModeGameOnly inputmode;
	PlayerController->SetInputMode(inputmode);
	SetVisibility(ESlateVisibility::Hidden);

	PlayerController->bIsInventoryVisible = false;
}

void UCInventoryWidget::OnItemSlotClicked(UCItemWidget* InItemWidget)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("OnItemSlotClicked"));

	if (MouseItem->GetVisibility() == ESlateVisibility::Hidden)
	{
		if (InItemWidget->GetVisibility() == ESlateVisibility::Hidden)
			return;
		
		else if (InItemWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			MouseItem->SetImageTexture(Items[InItemWidget->GetItemNum()]->ItemTexture);
			MouseItem->SetItemNum(InItemWidget->GetItemNum());
			MouseItem->SetItemCount(InItemWidget->GetItemCount());
			MouseItem->SetVisibleWithCount(ESlateVisibility::Visible);

			InItemWidget->SetVisibleWithCount(ESlateVisibility::Hidden);
			return;
		}
	}
	else if (MouseItem->GetVisibility() == ESlateVisibility::Visible)
	{
		if (InItemWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			InItemWidget->SetImageTexture(Items[MouseItem->GetItemNum()]->ItemTexture);
			InItemWidget->SetItemNum(MouseItem->GetItemNum());
			InItemWidget->SetItemCount(MouseItem->GetItemCount());
			InItemWidget->SetVisibleWithCount(ESlateVisibility::Visible);

			MouseItem->SetVisibleWithCount(ESlateVisibility::Hidden);

			return;
		}

		else if (InItemWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			UTexture2D* textureTemp = Items[MouseItem->GetItemNum()]->ItemTexture;
			int itemNumTemp = MouseItem->GetItemNum();
			int itemCountTemp = MouseItem->GetItemCount();

			MouseItem->SetImageTexture(Items[InItemWidget->GetItemNum()]->ItemTexture);
			MouseItem->SetItemNum(InItemWidget->GetItemNum());
			MouseItem->SetItemCount(InItemWidget->GetItemCount());

			InItemWidget->SetImageTexture(textureTemp);
			InItemWidget->SetItemNum(itemNumTemp);
			InItemWidget->SetItemCount(itemCountTemp);

			return;
		}
	}
}
