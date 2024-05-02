// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_RPG_SeriesCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Objects/CInteractionActor.h"
#include "UE5_RPG_SeriesPlayerController.h"

AUE5_RPG_SeriesCharacter::AUE5_RPG_SeriesCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create CapsuleCollision
	InteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(GetMesh());
	InteractCollision->SetCapsuleHalfHeight(88.f);
	InteractCollision->SetCapsuleRadius(44.f);
	InteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUE5_RPG_SeriesCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &AUE5_RPG_SeriesCharacter::OnInteracion);
	InteractCollision->OnComponentEndOverlap.AddDynamic(this, &AUE5_RPG_SeriesCharacter::OffInteraction);
}

void AUE5_RPG_SeriesCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

void AUE5_RPG_SeriesCharacter::OnInteracion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUE5_RPG_SeriesPlayerController* controller = Cast<AUE5_RPG_SeriesPlayerController>(GetController());
	if (controller == nullptr)
		return;

	controller->AddInteractionActor(OtherActor);
}

void AUE5_RPG_SeriesCharacter::OffInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUE5_RPG_SeriesPlayerController* controller = Cast<AUE5_RPG_SeriesPlayerController>(GetController());
	if (controller == nullptr)
		return;

	controller->RemoveInteractionActor(OtherActor);
}
