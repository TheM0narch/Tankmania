// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	NotAbleToShoot,AbleToShoot
};

class UBarrel;
class UTurret;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKMANIA_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()


public:	

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Init(UBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::NotAbleToShoot;

private:

	// Sets default values for this component's properties
	UTankAimComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrel(FVector AimDirection);

	bool IsMoving();

	double LastFire = 0;

	FVector AimDirection;

	UBarrel* Barrel = nullptr;

	UTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTime = 4;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UClass* MissileBlueprint;
};
