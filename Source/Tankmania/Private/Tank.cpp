// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = Health;
}

float ATank::GetHealthPerc() const
{
	return (float)CurrentHealth / (float)Health;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 Damage = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageTaken = FMath::Clamp(Damage, 0, CurrentHealth);
	CurrentHealth -= DamageTaken;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageTaken;
}


