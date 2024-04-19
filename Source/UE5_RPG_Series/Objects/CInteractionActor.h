#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CInteractionActor.generated.h"

UCLASS()
class UE5_RPG_SERIES_API ACInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACInteractionActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void TryInteraction();

private:
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

public:
	UPROPERTY(VisibleAnywhere)
	class UCInteractionComponent* InteractionComp;

};
