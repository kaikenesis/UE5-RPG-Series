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
	void Update();

	void AddItem(int InItemNum = -1, int InItemValue = 0);
	void UseItem(int InItemNum = -1, int InItemValue = 0);

	void UpdateWidget();

	void ShowWidget();

	class UCItemWidget* GetMouseItemWidget();

public:
	UFUNCTION()
	void OnCloseInventoryClicked();

public:
	TSubclassOf<class UCInventoryWidget> InventoryWidgetClass;
	TSubclassOf<class UCItemWidget> ItemWidgetClass;

	class UCInventoryWidget* InventoryWidget;
	class UCItemWidget* MouseItemWidget;
	
	class AUE5_RPG_SeriesPlayerController* OwnerController;
};
