#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventorySystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_RPG_SERIES_API UCInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInventorySystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Init();
	void AddItem(int InItemNum = -1);

public:
	TSubclassOf<class UCInventoryWidget> InventoryWidgetClass;
	class UCInventoryWidget* InventoryWidget;
};
