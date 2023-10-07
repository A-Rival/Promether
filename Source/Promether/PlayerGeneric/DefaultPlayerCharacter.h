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
	void	Attack();
	UFUNCTION(BlueprintNativeEvent)
	float	TakeDamage(	float Damage,
								struct FDamageEvent const& DamageEvent,
								AController* EventInstigator,
								AActor* DamageCauser )					override;





	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill1();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill1();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill1();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill2();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill2();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill2();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill3();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill3();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill3();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill4();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill4();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill4();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill5();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill5();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill5();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill6();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill6();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill6();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Skill7();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Skill7();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Skill7();

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

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
