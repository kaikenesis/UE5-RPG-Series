#include "Components/CInventorySystem.h"
#include "Widgets/CInventoryWidget.h"
#include "Widgets/CItemWidget.h"
#include "UE5_RPG_SeriesPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UCInventorySystem::UCInventorySystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UCInventoryWidget> widgetAsset(TEXT("/Game/TopDown/Blueprints/WB_Inventory"));
	if(widgetAsset.Succeeded() == true)
		InventoryWidgetClass = widgetAsset.Class;

	ConstructorHelpers::FClassFinder<UCItemWidget> itemWidgetAsset(TEXT("/Game/TopDown/Blueprints/WB_ItemSegment"));
	if (itemWidgetAsset.Succeeded() == true)
		ItemWidgetClass = itemWidgetAsset.Class;
}


void UCInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	Init();
}


void UCInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MouseItemWidget->IsSlotVisibility() == true)
	{
		Update();
	}
}

void UCInventorySystem::Init()
{

	AUE5_RPG_SeriesPlayerController* ownerController = Cast<AUE5_RPG_SeriesPlayerController>(GetOwner());
	if (ownerController != nullptr)
	{
		OwnerController = ownerController;

		MouseItemWidget = CreateWidget<UCItemWidget>(OwnerController, ItemWidgetClass);
		MouseItemWidget->AddToViewport();
		MouseItemWidget->Init();

		InventoryWidget = CreateWidget<UCInventoryWidget>(OwnerController, InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryWidget->OnCloseInventoryClicked.AddDynamic(this, &UCInventorySystem::OnCloseInventoryClicked);
	}
}

void UCInventorySystem::Update()
{
	UpdateWidget();
}

void UCInventorySystem::AddItem(int InItemNum, int InItemValue)
{
	InventoryWidget->CheckItem(false, InItemNum, InItemValue);
}

void UCInventorySystem::UseItem(int InItemNum, int InItemValue)
{
	InventoryWidget->CheckItem(true, InItemNum, InItemValue);
}

void UCInventorySystem::UpdateWidget()
{
	FVector2D mousePosition = FVector2D::ZeroVector;
	OwnerController->GetMousePosition(mousePosition.X, mousePosition.Y);

	MouseItemWidget->SetPositionInViewport(mousePosition);
}

void UCInventorySystem::ShowWidget()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	MouseItemWidget->SetVisibility(ESlateVisibility::Visible);
}

UCItemWidget* UCInventorySystem::GetMouseItemWidget()
{
	return MouseItemWidget;
}

void UCInventorySystem::OnCloseInventoryClicked()
{
	MouseItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

