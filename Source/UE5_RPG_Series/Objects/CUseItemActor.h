#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CUseItemActor.generated.h"

UCLASS()
class UE5_RPG_SERIES_API ACUseItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACUseItemActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	class UBoxComponent* BoxComp;
	TSubclassOf<class UIInventory> InterfaceClass;

	UPROPERTY(EditAnywhere)
	int ItemNum = -1;

	UPROPERTY(EditAnywhere)
	int ItemValue = 0;
};
