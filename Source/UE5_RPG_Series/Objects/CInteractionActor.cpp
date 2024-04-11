#include "CInteractionActor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "UE5_RPG_SeriesPlayerController.h"

ACInteractionActor::ACInteractionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);
	Collision->SetCapsuleHalfHeight(88.f);
	Collision->SetCapsuleRadius(44.f);
}

void ACInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACInteractionActor::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ACInteractionActor::OnEndOverlap);
}

void ACInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACInteractionActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character == nullptr)
		return;

	AUE5_RPG_SeriesPlayerController* controller = Cast<AUE5_RPG_SeriesPlayerController>(character->GetController());
	if (controller == nullptr)
		return;

	controller->CanInteraction();
}

void ACInteractionActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character == nullptr)
		return;

	AUE5_RPG_SeriesPlayerController* controller = Cast<AUE5_RPG_SeriesPlayerController>(character->GetController());
	if (controller == nullptr)
		return;

	controller->CannotInteraction();
}

