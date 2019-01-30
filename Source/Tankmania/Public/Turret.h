// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */

//make it show in the BP
UCLASS( meta = (BlueprintSpawnableComponent))
class TANKMANIA_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateTurret(float RotationDegrees);

	UPROPERTY(EditAnywhere, Category = "Degrees")
	float MaxRotationDegrees = 20;
	
	
};
