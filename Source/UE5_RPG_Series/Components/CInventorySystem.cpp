#include "Components/CInventorySystem.h"
#include "Widgets/CInventoryWidget.h"
#include "UE5_RPG_SeriesPlayerController.h"

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
		InventoryWidget = CreateWidget<UCInventoryWidget>(ownerController, InventoryWidgetClass);
		InventoryWidget->AddToViewport();
	}
}

void UCInventorySystem::AddItem(int InItemNum)
{
	InventoryWidget->CheckItem(InItemNum);
}

