#include "CInteractionActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/CInteractionComponent.h"
#include "GameFramework/Character.h"
#include "UE5_RPG_SeriesPlayerController.h"

ACInteractionActor::ACInteractionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	InteractionComp = CreateDefaultSubobject<UCInteractionComponent>(TEXT("InteractComp"));
}

void ACInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

