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
		void Skill4_End();
	//Override me
	UFUNCTION(BlueprintImplementableEvent)
		void BP_Skill4_End();
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_Skill4_End();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TMap<EStats, float> DefaultStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TMap<CooldownType, float> CooldownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TMap<EMaxStats, float> DefaultMaxStats;

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
};
