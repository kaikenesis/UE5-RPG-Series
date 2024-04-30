#include "Widgets/CInventoryWidget.h"
#include "Engine/DataTable.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
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

	PlayerController = Cast<AUE5_RPG_SeriesPlayerController>(GetOwningPlayer());

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
				ItemWidgets.Add(itemWidget);
			}
		}
	}
}

void UCInventoryWidget::CheckItem(int InItemNum)
{
	for (const auto& itemWidget : ItemWidgets)
	{
		if (itemWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			if (itemWidget->GetItemNum() == Items[InItemNum - 1]->ItemNum)
			{
				IncreaseItem(itemWidget, InItemNum);
				return;
			}
		}

		else
		{
			AddItem(itemWidget, InItemNum);
			return;
		}
	}
}

void UCInventoryWidget::IncreaseItem(UCItemWidget* InWidget, int InItemNum)
{
	InWidget->IncreaseItemCount();
}

void UCInventoryWidget::AddItem(class UCItemWidget* InWidget, int InItemNum)
{
	if (InWidget != nullptr)
	{
		InWidget->SetImageTexture(Items[InItemNum - 1]->ItemTexture);
		InWidget->IncreaseItemCount();
		InWidget->SetItemNum(InItemNum);

		InWidget->SetVisibleWithCount(ESlateVisibility::Visible);
	}

	return;
}
