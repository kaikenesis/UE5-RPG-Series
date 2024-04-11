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

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* Collision;

};
