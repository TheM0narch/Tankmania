// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */

//make it show in the BP
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKMANIA_API UBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float ElevationSpeed);

private:
	UPROPERTY(EditAnywhere, Category="Degrees")
	float MaxDegrees = 10;

	//45 deg because after that the range starts falling 
	//and you really get two solutions to a target
	UPROPERTY(EditAnywhere, Category = "Degrees")
	float MaxElevationDegrees = 45;

	UPROPERTY(EditAnywhere, Category = "Degrees")
	float MinElevationDegrees = 0;
	
	
};
