// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!PossesedTank)
		{
			return;
		}
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!ensure(GetPawn()))
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!(PlayerTank && ControlledTank))
	{
		return;
	}
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim to the player
	auto AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimComponent->GetFiringState() == EFiringState::AbleToShoot)
	{
		AimComponent->Fire();
	}
}



