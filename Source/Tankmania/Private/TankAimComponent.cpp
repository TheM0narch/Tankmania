// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "Barrel.h"
#include "Turret.h"
#include "Missile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFire = FPlatformTime::Seconds();
}

void UTankAimComponent::Init(UBarrel* BarrelToSet, UTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (((FPlatformTime::Seconds() - LastFire) < ReloadTime) || IsMoving())
	{
		FiringState = EFiringState::NotAbleToShoot;
	}
	else
	{
		FiringState = EFiringState::AbleToShoot;
	}
}

EFiringState UTankAimComponent::GetFiringState() const
{
	return FiringState;
}


bool UTankAimComponent::IsMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);

}

void UTankAimComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}
	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimComponent::MoveBarrel(FVector TargetAimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = TargetAimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	//yaw the shortest way
	Barrel->ElevateBarrel(DeltaRotation.Pitch);
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotation.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotation.Yaw);
	}
}

void UTankAimComponent::Fire()
{
	if (FiringState != EFiringState::NotAbleToShoot)
	{
		if (!ensure(Barrel))
		{
			return;
		}
		if (!ensure(MissileBlueprint))
		{
			return;
		}
		auto Missile = GetWorld()->SpawnActor<AMissile>(MissileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Missile->LaunchMissile(LaunchSpeed);
		LastFire = FPlatformTime::Seconds();
	}
}

