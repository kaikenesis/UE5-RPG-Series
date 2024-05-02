#include "Objects/CUseItemActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/IInventory.h"
#include "GameFramework/Character.h"
#include "UE5_RPG_SeriesPlayerController.h"

ACUseItemActor::ACUseItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetBoxExtent(FVector(150.f, 150.f, 60.f));

	ConstructorHelpers::FClassFinder<UIInventory> asset(TEXT("/Script/CoreUObject.Class'/Script/UE5_RPG_Series.IInventory'"));
	if (asset.Succeeded())
		InterfaceClass = asset.Class;
}

void ACUseItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACUseItemActor::OnBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACUseItemActor::OnEndOverlap);
}

void ACUseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACUseItemActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (character != nullptr)
	{
		AUE5_RPG_SeriesPlayerController* playerController = Cast<AUE5_RPG_SeriesPlayerController>(character->GetController());
		if (playerController != nullptr)
		{
			if (UKismetSystemLibrary::DoesImplementInterface(playerController, InterfaceClass))
			{
				if (ItemNum < 0) return;
				playerController->UseItem_Interface(ItemNum, ItemValue);
			}
		}
	}
}

void ACUseItemActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

