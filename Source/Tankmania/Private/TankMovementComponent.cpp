// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Track.h"


void UTankMovementComponent::Init(UTrack* LeftTrackToSet, UTrack* RightTrackToSet)
{
	if (!ensure (LeftTrackToSet && RightTrackToSet))
	{
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


//Pathfinding for the AI Tanks
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//get the normal vector of the tank faceing forward
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	//get the normal vector in which the Ai has to move
	auto AIForwardVector = MoveVelocity.GetSafeNormal();
	auto AIDotProductVectorForMoveForward = FVector::DotProduct(TankForwardVector, AIForwardVector);
	auto AICrossProductVectorForTurnRight = FVector::CrossProduct(TankForwardVector, AIForwardVector).Z;

	MoveForward(AIDotProductVectorForMoveForward);
	TurnRight(AICrossProductVectorForTurnRight);

}

void UTankMovementComponent::MoveForward(float Speed)
{
	if (!ensure (LeftTrack && RightTrack))
	{
		return;
	}
	LeftTrack->SetTrack(Speed);
	RightTrack->SetTrack(Speed);
}


void UTankMovementComponent::TurnRight(float Speed)
{
	if (!ensure (LeftTrack && RightTrack))
	{
		return;
	}
	LeftTrack->SetTrack(Speed);
	RightTrack->SetTrack(-Speed);
}



