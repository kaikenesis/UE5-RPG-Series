#include "Components/CInventorySystem.h"
#include "Widgets/CInventoryWidget.h"

UCInventorySystem::UCInventorySystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UCInventoryWidget> widgetAsset(TEXT("/Game/TopDown/Blueprints/WB_Inventory"));
}


void UCInventorySystem::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

