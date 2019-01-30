// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTrack;

/**
 * Used in driving the player tank and controlling the AI tanks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKMANIA_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category= "Input")
	void MoveForward(float Speed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Init(UTrack* LeftTrackToSet, UTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TurnRight(float Speed);

	

private:
	//Used in pathfinding
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTrack* RightTrack = nullptr;

	UTrack* LeftTrack = nullptr;	
};
