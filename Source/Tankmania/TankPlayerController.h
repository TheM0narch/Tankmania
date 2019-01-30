// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimComponent;

/**
 *
 */
UCLASS()
class TANKMANIA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimComponent(UTankAimComponent* AimComponentRef);

	UFUNCTION()
	void OnTankDeath();

private:

	virtual void BeginPlay() override;

	void SetPawn(APawn * InPawn);

	virtual void Tick(float DeltaTime) override;

	//function to move the barrel to the place the crosshair is pointing
	void AimToCrosshair();

	//Return OUT parameter
	//true if hit something on the landscape
	//out parameters works by passing reference 
	//bool bGetSightHitLocation(FVector& OutHitLocation) const;

	bool bGetCrosshairHitLocation(FVector& OutHitLocation);

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.3333;
};
