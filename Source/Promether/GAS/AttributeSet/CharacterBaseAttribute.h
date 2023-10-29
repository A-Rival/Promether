// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterBaseAttribute.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROMETHER_API UCharacterBaseAttribute : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	//Replicated
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadonly, Category = "Team", ReplicatedUsing = OnRep_Team)
	FGameplayAttributeData Team;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, Team)

	UPROPERTY(BlueprintReadonly, Category = "XP", ReplicatedUsing = OnRep_XP)
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, XP)

	UPROPERTY(BlueprintReadonly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, Health)

	UPROPERTY(BlueprintReadonly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, MaxHealth)

	UPROPERTY(BlueprintReadonly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, Mana)

	UPROPERTY(BlueprintReadonly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, MaxMana)

	UFUNCTION()
	virtual void OnRep_Team(const FGameplayAttributeData& OldTeam);
	UFUNCTION()
	virtual void OnRep_XP(const FGameplayAttributeData& OldXP);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

public:
	//Not Replicated
	UPROPERTY(BlueprintReadonly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttribute, Damage)

};
