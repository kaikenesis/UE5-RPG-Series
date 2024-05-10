#include "Widgets/CItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetInputLibrary.h"
#include "Styling/SlateBrush.h"

void UCItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCItemWidget::Init()
{
	ItemCount->SetVisibility(ESlateVisibility::Hidden);
	ItemImage->SetVisibility(ESlateVisibility::Hidden);
}

void UCItemWidget::SetImageTexture(UTexture2D* InTexture)
{
	ItemImage->SetBrushFromTexture(InTexture);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, InTexture->GetName());
}

void UCItemWidget::SetItemCount(int InValue)
{
	Count = InValue;
	Count = FMath::Clamp(Count, 0, 99);
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
	if (Count >= 99)
		bCanStack = false;
	else if (Count < 99)
		bCanStack = true;
}

void UCItemWidget::IncreaseItemCount(int InValue)
{
	Count += InValue;
	Count = FMath::Clamp(Count, 0, 99);
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
	if (Count >= 99)
		bCanStack = false;
}

void UCItemWidget::DecreaseItemCount(int InValue)
{
	Count -= InValue;
	Count = FMath::Clamp(Count, 0, 99);
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
	if (bCanStack == false && Count < 99)
		bCanStack = true;
}

void UCItemWidget::SetVisibleWithCount(ESlateVisibility InVisibility)
{
	ItemCount->SetVisibility(InVisibility);
	ItemImage->SetVisibility(InVisibility);
}

void UCItemWidget::SetVisibleWithoutCount(ESlateVisibility InVisibility)
{
	ItemCount->SetVisibility(ESlateVisibility::Hidden);
	ItemImage->SetVisibility(InVisibility);
}

bool UCItemWidget::IsSlotVisibility()
{
	if (ItemImage->GetVisibility() == ESlateVisibility::Visible || ItemCount->GetVisibility() == ESlateVisibility::Visible)
		return true;

	return false;
}

void UCItemWidget::BindItemSlotButton()
{
	Button->OnClicked.AddDynamic(this, &UCItemWidget::OnClicked);
}

UObject* UCItemWidget::GetImageTexture()
{
	FSlateBrush brush = ItemImage->Brush;

	if (brush.GetResourceObject() != nullptr)
		return brush.GetResourceObject();

	return nullptr;
}

void UCItemWidget::OnClicked()
{
	if (OnItemSlotClicked.IsBound())
		OnItemSlotClicked.Broadcast(this);
}
