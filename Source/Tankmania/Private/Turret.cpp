// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"

void UTurret::RotateTurret(float RotationDegrees)
{
	RotationDegrees = FMath::Clamp<float>(RotationDegrees, -1, +1);
	auto RotationChange = RotationDegrees * MaxRotationDegrees * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


