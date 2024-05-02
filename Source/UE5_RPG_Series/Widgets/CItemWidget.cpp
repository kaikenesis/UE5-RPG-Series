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
	SetVisibility(ESlateVisibility::Hidden);
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
}

void UCItemWidget::IncreaseItemCount(int InValue)
{
	Count += InValue;
	Count = FMath::Clamp(Count, 0, 99);
	ItemCount->SetText(UKismetTextLibrary::Conv_IntToText(Count));
}

void UCItemWidget::DecreaseItemCount(int InValue)
{
	Count -= InValue;
	Count = FMath::Clamp(Count, 0, 99);
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
