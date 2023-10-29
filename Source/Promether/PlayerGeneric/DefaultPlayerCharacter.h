// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "DefaultPlayerState.h"
#include "../GAS/DefaultAbilitySystemComponent.h"
#include "../GAS/AttributeSet/CharacterBaseAttribute.h"
#include "../GAS/Abilities/CharacterGameplayAbility.h"
#include "DefaultPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ADefaultPlayerCharacter*, Character);

UCLASS()
class PROMETHER_API ADefaultPlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual int32 GetAbilityLevel(EDefaultAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();
	virtual void beginDead();

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetXP() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetCalculatedLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attribute")
	float GetMaxMana() const;

protected:
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UDefaultAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterBaseAttribute> Attribute;

	FGameplayTag DeadTag;
	FGameplayTag TeamTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "Abilities")
	TArray<TSubclassOf<UCharacterGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	void InitializeStartingValues(ADefaultPlayerState* State);

	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);

	virtual void OnRep_PlayerState() override;

	bool ASCInputBound = false;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
};
