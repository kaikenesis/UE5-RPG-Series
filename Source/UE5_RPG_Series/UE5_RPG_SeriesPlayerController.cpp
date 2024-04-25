// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_RPG_SeriesPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UE5_RPG_SeriesCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Objects/CInteractionActor.h"
#include "Components/CInventorySystem.h"
#include "Components/CInteractionComponent.h"

AUE5_RPG_SeriesPlayerController::AUE5_RPG_SeriesPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	InventorySystem = CreateDefaultSubobject<UCInventorySystem>(TEXT("InventorySystem"));
}

void AUE5_RPG_SeriesPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AUE5_RPG_SeriesPlayerController::AddInteractionActor(AActor* OtherActor)
{
	ACInteractionActor* interactionActor = Cast<ACInteractionActor>(OtherActor);
	if (interactionActor != nullptr)
		InteractActors.Add(interactionActor);
	
	if (InteractActors.Num() > 0)
		bCanInteraction = true;
	else
		bCanInteraction = false;
}

void AUE5_RPG_SeriesPlayerController::RemoveInteractionActor(AActor* OtherActor)
{
	ACInteractionActor* interactionActor = Cast<ACInteractionActor>(OtherActor);
	if (interactionActor != nullptr)
		InteractActors.RemoveSingle(interactionActor);

	if (InteractActors.Num() > 0)
		bCanInteraction = true;
	else
		bCanInteraction = false;
}

void AUE5_RPG_SeriesPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AUE5_RPG_SeriesPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AUE5_RPG_SeriesPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AUE5_RPG_SeriesPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AUE5_RPG_SeriesPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AUE5_RPG_SeriesPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AUE5_RPG_SeriesPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AUE5_RPG_SeriesPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AUE5_RPG_SeriesPlayerController::OnTouchReleased);
	}

	{
		InputComponent->BindKey(EKeys::F, IE_Pressed, this, &AUE5_RPG_SeriesPlayerController::DoInteraction);
	}
}

void AUE5_RPG_SeriesPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AUE5_RPG_SeriesPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AUE5_RPG_SeriesPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AUE5_RPG_SeriesPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AUE5_RPG_SeriesPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AUE5_RPG_SeriesPlayerController::DoInteraction()
{
	if (bCanInteraction == false)
		return;

	for (const auto interactActor : InteractActors)
	{
		InventorySystem->AddItem(interactActor->InteractionComp->ItemNum);
	}
}
