// Fill out your copyright notice in the Description page of Project Settings.

#include "Track.h"

UTrack::UTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTrack::OnHit);
}

void UTrack::SidewaysForce()
{
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Correction = -SlipSpeed / DeltaTime * GetRightVector();
	auto Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (Root->GetMass() * Correction) / 2;
	Root->AddForce(CorrectionForce);
}

void UTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Drive();
	SidewaysForce();
	CurrentTrack = 0;
}

void UTrack::SetTrack(float Track)
{
	CurrentTrack = FMath::Clamp<float>(CurrentTrack + Track, -2, 2);
}

void UTrack::Drive()
{
	auto ForceApplied = GetForwardVector() * FMath::Clamp<float>(CurrentTrack, -0.75f, 0.75f) * MaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}

