#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInteractionComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	None,
	Resource
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_RPG_SERIES_API UCInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DoInteractionResource();

public:
	EInteractType InteractType;
};
