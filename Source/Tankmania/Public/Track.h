// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Track.generated.h"

/**
 * 
 */
 //make it show in the BP
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKMANIA_API UTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTrack(float Track);

	//max force in newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDriveForce = 60000000;

private:
	UTrack();

	virtual void BeginPlay() override;

	void SidewaysForce();

	void Drive();

	float CurrentTrack = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
