// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "../PrometherEnum.h"
#include "DefaultPlayerCharacter.generated.h"

UCLASS()
class PROMETHER_API ADefaultPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
					ADefaultPlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void			Attack()											;
	virtual float	TakeDamage(	float Damage,
								struct FDamageEvent const& DamageEvent,
								AController* EventInstigator,
								AActor* DamageCauser )					override;

	UFUNCTION(BlueprintNativeEvent)
	void Skill1();
	UFUNCTION(BlueprintNativeEvent)
	void Skill2();
	UFUNCTION(BlueprintNativeEvent)
	void Skill3();
	UFUNCTION(BlueprintNativeEvent)
	void Skill4();

	UFUNCTION(BlueprintNativeEvent)
	void Skill5();
	UFUNCTION(BlueprintNativeEvent)
	void Skill6();
	UFUNCTION(BlueprintNativeEvent)
	void Skill7();

	float			GetHealth()											const { return Health; }
	float			GetHPRegeneration()									const { return HPRegeneration; }
	float			GetHealAndShieldpower()								const { return HealAndShieldpower; }
	float			GetArmor()											const { return Armor; }
	float			GetMagicResistance()								const { return MagicResistance; }
	float			GetTenacity()										const { return Tenacity; }
	float			GetSlowRisist()										const { return SlowRisist; }
	float			GetAttackSpeed()									const { return AttackSpeed; }
	float			GetAttackDamage()									const { return AttackDamage; }
	float			GetAbilityPower()									const { return AbilityPower; }
	float			GetCriticalStrikeChance()							const { return CriticalStrikeChance; }
	float			GetCriticalStrikeDamage()							const { return CriticalStrikeDamage; }
	float			GetArmorPenetration()								const { return ArmorPenetration; }
	float			GetMagicPenetration()								const { return MagicPenetration; }
	float			GetLifeSteal()										const { return LifeSteal; }
	float			GetPhysicalVamp()									const { return PhysicalVamp; }
	float			GetOmnivamp()										const { return Omnivamp; }
	float			GetAbilityHaste()									const { return AbilityHaste; }
	const float*	GetCooldownDuration()								const { return CooldownDuration; }
	float			GetMana()											const { return Mana; }
	float			GetManaRegeneration()								const { return ManaRegeneration; }
	float			GetEnergy()											const { return Energy; }
	float			GetEnergyRegeneration()								const { return EnergyRegeneration; }
	float			GetAttackRange()									const { return AttackRange; }
	float			GetMovementSpeed()									const { return MovementSpeed; }
	float			GetGoldGeneration()									const { return GoldGeneration; }
	float			GetAttackDamageGrowth()								const { return AttackDamageGrowth; }
	float			GetAttackSpeedGrowth()								const { return AttackSpeedGrowth; }
	float			GetArmorGrowth()									const { return ArmorGrowth; }
	float			GetMagicResistanceGrowth()							const { return MagicResistanceGrowth; }
	float			GetHealthGrowth()									const { return HealthGrowth; }
	float			GetHealthRegenerationGrowth()						const { return HealthRegenerationGrowth; }
	float			GetManaGrowth()										const { return ManaGrowth; }
	float			GetManaRegenerationGrowth()							const { return ManaRegenerationGrowth; }

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float HPRegeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float HealAndShieldpower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float MagicResistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float Tenacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Defensive")
	float SlowRisist;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float AbilityPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float CriticalStrikeChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float CriticalStrikeDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float ArmorPenetration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float MagicPenetration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float LifeSteal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float PhysicalVamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Offensive")
	float Omnivamp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Haste")
	float AbilityHaste;

	UPROPERTY(EditAnywhere, Category = "Stats|Utility|Haste")
	float CooldownDuration[(uint8)CooldownType::SIZE] = { 0.0f, };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Resource")
	float Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Resource")
	float ManaRegeneration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Resource")
	float Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Resource")
	float EnergyRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility")
	float AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Utility|Non-Combat")
	float GoldGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float AttackDamageGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float AttackSpeedGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float ArmorGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float MagicResistanceGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float HealthGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float HealthRegenerationGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float ManaGrowth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Increasing Statistics")
	float ManaRegenerationGrowth;
};
