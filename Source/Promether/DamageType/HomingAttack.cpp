// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingAttack.h"
#include "../PlayerGeneric/DefaultPlayerCharacter.h"
#include "../PlayerGeneric/DefaultPlayerState.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHomingAttack::AHomingAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 200;
	ProjectileMovement->MaxSpeed = 200;
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 200;
	ProjectileMovement->Velocity = { 0, 0, 0 };
	ProjectileMovement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void AHomingAttack::BeginPlay()
{
	Super::BeginPlay();

	ADefaultPlayerState* State = Cast<APawn>(GetOwner())->GetPlayerState<ADefaultPlayerState>();
	if (!State) return;
	if (!State->GetCurrentAttackTarget())
	{
		UE_LOG(LogTemp, Error, TEXT("No Target"));
		return;
	}

	Target = State->GetCurrentAttackTarget();
	ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
}

// Called every frame
void AHomingAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

