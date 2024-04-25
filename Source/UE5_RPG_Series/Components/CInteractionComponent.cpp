#include "Components/CInteractionComponent.h"

UCInteractionComponent::UCInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCInteractionComponent::DoInteractionResource()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Interaction"));
}

