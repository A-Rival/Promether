// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerCharacter.h"
#include "DefaultPlayerState.h"
#include "Engine/DamageEvents.h"

ADefaultPlayerCharacter::ADefaultPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(true);
	bUseControllerRotationYaw = false;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 0.0f, 0.0f));
	CameraSpringArm->SetAbsolute(false, true, true);
	CameraSpringArm->TargetArmLength = 2000.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	CameraSpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	Health = 0.0f;
	HPRegeneration = 0.0f;
	HealAndShieldpower = 0.0f;
	Armor = 0.0f;
	MagicResistance = 0.0f;
	Tenacity = 0.0f;
	SlowRisist = 0.0f;
	AttackSpeed = 0.0f;
	AttackDamage = 0.0f;
	AbilityPower = 0.0f;
	CriticalStrikeChance = 0.0f;
	CriticalStrikeDamage = 0.0f;
	ArmorPenetration = 0.0f;
	MagicPenetration = 0.0f;
	LifeSteal = 0.0f;
	PhysicalVamp = 0.0f;
	Omnivamp = 0.0f;
	AbilityHaste = 0.0f;
	Mana = 0.0f;
	ManaRegeneration = 0.0f;
	Energy = 0.0f;
	EnergyRegeneration = 0.0f;
	AttackRange = 0.0f;
	MovementSpeed = 0.0f;
	GoldGeneration = 0.0f;
	AttackDamageGrowth = 0.0f;
	AttackSpeedGrowth = 0.0f;
	ArmorGrowth = 0.0f;
	MagicResistanceGrowth = 0.0f;
	HealthGrowth = 0.0f;
	HealthRegenerationGrowth = 0.0f;
	ManaGrowth = 0.0f;
	ManaRegenerationGrowth = 0.0f;
}

void ADefaultPlayerCharacter::Tick(float DeltaTime)
{
	/*
	if (GetPlayerState<ADefaultPlayerState>())
	{
		if (!GPlayInEditorID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Server %s State : %d"), *GetName(), GetPlayerState<ADefaultPlayerState>()->GetState());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Client %d %s State : %d"), GPlayInEditorID, *GetName(), GetPlayerState<ADefaultPlayerState>()->GetState());
		}
	}
	*/
}

void ADefaultPlayerCharacter::Attack_Implementation()
{
}

float ADefaultPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ReturnValue = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("TakeDamage Called On Server"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TakeDamage Called On Client"));
	}

	if (HasAuthority())
	{
		if (ADefaultPlayerState* MyState = this->GetInstigatorController()->GetPlayerState<ADefaultPlayerState>())
		{
			if (ADefaultPlayerState* EventInstigatorState = EventInstigator->GetPlayerState<ADefaultPlayerState>())
			{
				float ADDamageMultiplier = 0;
				float APDamageMultiplier = 0;

				if (MyState->Stats.Armor >= 0)
					ADDamageMultiplier = 100 / (100 + MyState->Stats.Armor);
				else
					ADDamageMultiplier = 2 - 100 / (100 - MyState->Stats.Armor);

				if (MyState->Stats.MagicResistance >= 0)
					APDamageMultiplier = 100 / (100 + MyState->Stats.MagicResistance);
				else
					APDamageMultiplier = 2 - 100 / (100 - MyState->Stats.MagicResistance);


				UE_LOG(LogTemp, Warning, TEXT("%s : ADDamageMultiplier : %f CalculatedDamage : %f"), *DamageCauser->GetName(), ADDamageMultiplier, DamageAmount * ADDamageMultiplier);
				UE_LOG(LogTemp, Warning, TEXT("%s : APDamageMultiplier : %f CalculatedDamage : %f"), *DamageCauser->GetName(), APDamageMultiplier, DamageAmount * APDamageMultiplier);

				if (Cast<UBaseAttack>(DamageEvent.DamageTypeClass->GetDefaultObject()))
				{
					UE_LOG(LogTemp, Warning, TEXT("DamageType : BaseAttack"));

					float UpdatedHealth = MyState->Stats.Health - EventInstigatorState->Stats.AttackDamage * ADDamageMultiplier;
					if (UpdatedHealth < 0)
					{
						MyState->Stats.Health = 0;
					}
					else
					{
						MyState->Stats.Health = UpdatedHealth;
					}

					UE_LOG(LogTemp, Warning, TEXT("Current Health : %f"), MyState->Stats.Health);
				}
				
			}
		}

		return ReturnValue;
	}
	else
	{
		return -1.0f;
	}
}

void ADefaultPlayerCharacter::Skill1_Implementation()
{
}

void ADefaultPlayerCharacter::Skill2_Implementation()
{
}

void ADefaultPlayerCharacter::Skill3_Implementation()
{
}

void ADefaultPlayerCharacter::Skill4_Implementation()
{
}

void ADefaultPlayerCharacter::Skill5_Implementation()
{
}

void ADefaultPlayerCharacter::Skill6_Implementation()
{
}

void ADefaultPlayerCharacter::Skill7_Implementation()
{
}
