// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include <iostream>
#include <map>

#include "../PrometherEnum.h"
#include "../GAS/AttributeSet/CharacterBaseAttribute.h"
#include "DefaultPlayerState.generated.h"

UCLASS()
class PROMETHER_API ADefaultPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
					ADefaultPlayerState();
	void			GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void			SetCharacterBPRef(UClass* Value)					{ CharacterBPRef = Value; }
	UClass*			GetCharacterBPRef()									const { return CharacterBPRef; }

	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState")
	TeamType		GetTeam() const;
	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|Attributes")
	float			GetXP() const;
	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|Attributes")
	float			GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|Attributes")
	float			GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|Attributes")
	float			GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|Attributes")
	float			GetMaxMana() const;

	class UCharacterBaseAttribute* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "DefaultPlayerState|UI")
	void ShowAbliityConfirmCancelText(bool ShowText);

	void			SetPlayerCamera(AActor* Actor)						{ PlayerCamera = Actor; }
	AActor*			GetPlayerCamera()									const { return PlayerCamera; }

	UFUNCTION(BlueprintCallable)
	int32			GetCharacterLevel()									const;

	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentAttackTarget() const { return CurrentAttackTarget; };
	UFUNCTION(BlueprintCallable)
	AActor* GetPreviousAttackTarget() const { return PreviousAttackTarget; };

	void SetCurrentAttackTarget(AActor* Target);
	UFUNCTION(Server, Reliable)
	void Server_SetCurrentAttackTarget(AActor* Target);
	UFUNCTION(Client, Reliable)
	void Client_SetCurrentAttackTarget(AActor* Target);

	void SetPreviousAttackTarget(AActor* Target);
	UFUNCTION(Server, Reliable)
	void Server_SetPreviousAttackTarget(AActor* Target);
	UFUNCTION(Client, Reliable)
	void Client_SetPreviousAttackTarget(AActor* Target);
	
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadWrite)
	TArray<float> Stats;
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadWrite)
	TArray<float> MaxStats;

	UPROPERTY(Replicated, Transient, BlueprintReadWrite)
	TArray<float> CooldownDuration;
	UPROPERTY(Replicated, Transient, BlueprintReadWrite)
	TArray<float> MaxCooldownDuration;

protected:
	class UDefaultAbilitySystemComponent* AbilitySystemComponent;
	class UCharacterBaseAttribute* Attribute;

	FGameplayTag DeadTag;
	FGameplayTag TeamTag;
	FGameplayTag EffectTag;

	FDelegateHandle TeamChangedDelegateHandle;
	FDelegateHandle XPChangedDelegateHandle;
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void TeamChanged(const FOnAttributeChangeData& Data);
	virtual void XPChanged(const FOnAttributeChangeData& Data);
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

private:
	UPROPERTY(Replicated, Transient)
	UClass* CharacterBPRef;

	UPROPERTY(Replicated, Transient)
	AActor* PlayerCamera;

	UPROPERTY(Replicated, Transient)
	AActor* CurrentAttackTarget;
	UPROPERTY(Replicated, Transient)
	AActor* PreviousAttackTarget;
};
