// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerCharacter.h"
#include "DefaultPlayerState.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

ADefaultPlayerCharacter::ADefaultPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(true);
	bUseControllerRotationYaw = false;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 0.0f, 0.0f));
	CameraSpringArm->SetAbsolute(false, true, true);
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	CameraSpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStats"), true);
	if (!CharStateEnum)
	{
		UE_LOG(LogTemp, Error, TEXT("EStats Missing"));
		return;
	}

	for (uint8 i = 0; i < (uint8)EStats::SIZE; i++)
		DefaultStats.Add(*CharStateEnum->GetNameByValue((uint8)i).ToString(), 0.0f);

	for (uint8 i = 0; i < (uint8)CooldownType::SIZE; i++)
		CooldownDuration.Add((CooldownType)i, 0.0f);
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
	//UGameplayStatics::ApplyDamage(Target, MyState->GetAttackDamage(), Cast<AController>(GetOwner()), this, UBaseAttack::StaticClass());
}

float ADefaultPlayerCharacter::TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
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

				if (MyState->Stats[(uint8)EStats::Armor] >= 0)
					ADDamageMultiplier = 100 / (100 + MyState->Stats[(uint8)EStats::Armor]);
				else
					ADDamageMultiplier = 2 - 100 / (100 - MyState->Stats[(uint8)EStats::Armor]);

				if (MyState->Stats[(uint8)EStats::MagicResistance] >= 0)
					APDamageMultiplier = 100 / (100 + MyState->Stats[(uint8)EStats::MagicResistance]);
				else
					APDamageMultiplier = 2 - 100 / (100 - MyState->Stats[(uint8)EStats::MagicResistance]);


				UE_LOG(LogTemp, Warning, TEXT("%s : ADDamageMultiplier : %f CalculatedDamage : %f"), *DamageCauser->GetName(), ADDamageMultiplier, DamageAmount * ADDamageMultiplier);
				UE_LOG(LogTemp, Warning, TEXT("%s : APDamageMultiplier : %f CalculatedDamage : %f"), *DamageCauser->GetName(), APDamageMultiplier, DamageAmount * APDamageMultiplier);

				if (Cast<UBaseAttack>(DamageEvent.DamageTypeClass->GetDefaultObject()))
				{
					UE_LOG(LogTemp, Warning, TEXT("DamageType : BaseAttack")); 

					float UpdatedHealth = MyState->Stats[(uint8)EStats::Health] - EventInstigatorState->Stats[(uint8)EStats::AttackDamage] * ADDamageMultiplier;
					if (UpdatedHealth < 0)
					{
						MyState->Stats[(uint8)EStats::Health] = 0;
					}
					else
					{
						MyState->Stats[(uint8)EStats::Health] = UpdatedHealth;
					}

					UE_LOG(LogTemp, Warning, TEXT("Current Health : %f"), MyState->Stats[(uint8)EStats::Health]);
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
	NetMulticast_Skill1();
}

void ADefaultPlayerCharacter::NetMulticast_Skill1_Implementation()
{
	BP_Skill1();
}

void ADefaultPlayerCharacter::Skill2_Implementation()
{
	NetMulticast_Skill2();
}

void ADefaultPlayerCharacter::NetMulticast_Skill2_Implementation()
{
	BP_Skill2();
}

void ADefaultPlayerCharacter::Skill3_Implementation()
{
	NetMulticast_Skill3();
}

void ADefaultPlayerCharacter::NetMulticast_Skill3_Implementation()
{
	BP_Skill3();
}

void ADefaultPlayerCharacter::Skill4_Implementation()
{
	NetMulticast_Skill4();
}

void ADefaultPlayerCharacter::NetMulticast_Skill4_Implementation()
{
	BP_Skill4();
}

void ADefaultPlayerCharacter::Skill5_Implementation()
{
	NetMulticast_Skill5();
}

void ADefaultPlayerCharacter::NetMulticast_Skill5_Implementation()
{
	BP_Skill5();
}

void ADefaultPlayerCharacter::Skill6_Implementation()
{
	NetMulticast_Skill6();
}

void ADefaultPlayerCharacter::NetMulticast_Skill6_Implementation()
{
	BP_Skill6();
}

void ADefaultPlayerCharacter::Skill7_Implementation()
{
	NetMulticast_Skill7();
}

void ADefaultPlayerCharacter::NetMulticast_Skill7_Implementation()
{
	BP_Skill7();
}
