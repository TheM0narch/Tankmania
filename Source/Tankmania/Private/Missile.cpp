// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"





// Sets default values
AMissile::AMissile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshCollision = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(MeshCollision);
	MeshCollision->SetNotifyRigidBodyCollision(true);
	MeshCollision->SetVisibility(false);

	BarrelBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Blast"));
	BarrelBlast->SetupAttachment(MeshCollision);

	MissileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Missile Movement"));
	MissileMovement->bAutoActivate = false;

	HitExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Hit Blast"));
	HitExplosion->SetupAttachment(MeshCollision);
	HitExplosion->bAutoActivate = false;

	ExplosionHitForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionHitForce->SetupAttachment(MeshCollision);

}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	MeshCollision->OnComponentHit.AddDynamic(this, &AMissile::OnHit);
}


void AMissile::LaunchMissile(float LaunchSpeed)
{
	MissileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	MissileMovement->Activate();
}

void AMissile::TimerEnd()
{
	Destroy();
}

void AMissile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	BarrelBlast->Deactivate();
	HitExplosion->Activate();
	ExplosionHitForce->FireImpulse();

	SetRootComponent(HitExplosion);
	MeshCollision->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, MissileDamage, GetActorLocation(), ExplosionHitForce->Radius, UDamageType::StaticClass(), TArray<AActor *>());

	SetLifeSpan(Delay);
}