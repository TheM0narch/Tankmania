// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class TANKMANIA_API AMissile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchMissile(float LaunchSpeed);

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void TimerEnd();

	UProjectileMovementComponent* MissileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Missile Components")
		UStaticMeshComponent* MeshCollision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Missile Components")
		UParticleSystemComponent* BarrelBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Missile Components")
		UParticleSystemComponent* HitExplosion = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Missile Components")
		URadialForceComponent* ExplosionHitForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Setup")
		float Delay = .1f;

	UPROPERTY(EditDefaultsOnly, Category = "Missile Setup")
		float  MissileDamage = 25.0f;

};