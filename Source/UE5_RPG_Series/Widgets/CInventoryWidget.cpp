#include "Widgets/CInventoryWidget.h"
#include "Engine/DataTable.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
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
		UHorizontalBox* containor = Cast<UHorizontalBox>(child);
		if (containor != nullptr)
			ItemContainors.Add(containor);
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
}

void UCInventoryWidget::CheckItem(int InItemNum)
{
	for (const auto& itemSlot : ItemSlots)
	{
		TArray<UWidget*> itemChildren = itemSlot->GetAllChildren();
		for (const auto& child : itemChildren)
		{
			UCItemWidget* itemWidget = Cast<UCItemWidget>(child);
			if (itemWidget != nullptr)
			{
				if (itemWidget->GetItemNum() == Items[InItemNum - 1]->ItemNum)
				{
					IncreaseItem(itemWidget, InItemNum);
					return;
				}
				break;
			}

			if (child == itemChildren[itemChildren.Num() - 1])
			{
				UCItemWidget* newItemWidget = AddItem(InItemNum);
				if (newItemWidget != nullptr)
				{
					itemSlot->AddChild(newItemWidget);

					newItemWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
					newItemWidget->SetPositionInViewport(FVector2D(0.0f, 0.0f));
					newItemWidget->SetDesiredSizeInViewport(FVector2D(90.f, 100.f));
					newItemWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
				}
				return;
			}
		}
	}
}

void UCInventoryWidget::IncreaseItem(UCItemWidget* InWidget, int InItemNum)
{
	InWidget->IncreaseItemCount();
}

UCItemWidget* UCInventoryWidget::AddItem(int InItemNum)
{
	UCItemWidget* itemWidget = CreateWidget<UCItemWidget>(this, ItemWidgetClass);
	if (itemWidget != nullptr)
	{
		itemWidget->SetImageTexture(Items[InItemNum - 1]->ItemTexture);
		itemWidget->IncreaseItemCount();
		itemWidget->SetItemNum(InItemNum);
	}

	return itemWidget;
}
