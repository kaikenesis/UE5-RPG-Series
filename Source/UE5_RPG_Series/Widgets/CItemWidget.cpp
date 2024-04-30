#include "Widgets/CItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetTextLibrary.h"
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
	SetVisibility(ESlateVisibility::Hidden);
}

void UCItemWidget::SetImageTexture(UTexture2D* InTexture)
{
	ItemImage->SetBrushFromTexture(InTexture);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, InTexture->GetName());
}

void UCItemWidget::IncreaseItemCount()
{
	Count++;
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
}

void UCItemWidget::DecreaseItemCount()
{
	Count--;
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
}

void UCItemWidget::SetVisibleWithCount(ESlateVisibility InVisibility)
{
	ItemCount->SetVisibility(InVisibility);
	SetVisibility(InVisibility);
}

void UCItemWidget::SetVisibleWithoutCount(ESlateVisibility InVisibility)
{
	ItemCount->SetVisibility(ESlateVisibility::Hidden);
	SetVisibility(InVisibility);
}

UObject* UCItemWidget::GetImageTexture()
{
	FSlateBrush brush = ItemImage->Brush;

	if (brush.GetResourceObject() != nullptr)
		return brush.GetResourceObject();

	return nullptr;
}
