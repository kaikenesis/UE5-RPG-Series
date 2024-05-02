#include "Components/CInventorySystem.h"
#include "Widgets/CInventoryWidget.h"
#include "UE5_RPG_SeriesPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UCInventorySystem::UCInventorySystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UCInventoryWidget> widgetAsset(TEXT("/Game/TopDown/Blueprints/WB_Inventory"));
	if(widgetAsset.Class != nullptr)
		InventoryWidgetClass = widgetAsset.Class;
}


void UCInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	Init();
}


void UCInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCInventorySystem::Init()
{

	AUE5_RPG_SeriesPlayerController* ownerController = Cast<AUE5_RPG_SeriesPlayerController>(GetOwner());
	if (ownerController != nullptr)
	{
		OwnerController = ownerController;
		InventoryWidget = CreateWidget<UCInventoryWidget>(OwnerController, InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
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
	mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(OwnerController);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, mousePosition.ToString());
	InventoryWidget->SetMouseItemPosition(mousePosition);
}

void UCInventorySystem::ShowWidget()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
}

