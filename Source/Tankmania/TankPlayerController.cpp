// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent))
	{
		return;
	}
	FoundAimComponent(AimComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank))
		{
			return;
		}
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimToCrosshair();
}


void ATankPlayerController::AimToCrosshair()
{
	if (!GetPawn())
	{
		return;
	}
	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent))
	{
		return;
	}

	FVector HitLocation = FVector(0);

	if (bGetCrosshairHitLocation(HitLocation))
	{
		AimComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::bGetCrosshairHitLocation(FVector& OutHitLocation)
{
	// Viewport Size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	bool bHit;
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX * CrosshairX, ViewportSizeY * CrosshairY);
	FHitResult HitResult;

	//Returns hit results from doing a collision query at a certain location on the screen
	bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_WorldStatic, false, HitResult);

	if (bHit)
	{
		OutHitLocation = HitResult.ImpactPoint;
	}

	return bHit;
}
