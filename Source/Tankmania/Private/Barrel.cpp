// Fill out your copyright notice in the Description page of Project Settings.

#include "Barrel.h"


void UBarrel::ElevateBarrel(float ElevationSpeed)
{
	ElevationSpeed = FMath::Clamp<float>(ElevationSpeed, -1, +1);
	auto ElevationChange = ElevationSpeed * MaxElevationDegrees * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}

