// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBaseAttribute.h"
#include "Net/UnrealNetwork.h"

void UCharacterBaseAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterBaseAttribute, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterBaseAttribute, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterBaseAttribute, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterBaseAttribute, MaxMana, COND_None, REPNOTIFY_Always);
}

void UCharacterBaseAttribute::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttribute, Health, OldHealth);
}

void UCharacterBaseAttribute::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttribute, MaxHealth, OldMaxHealth);
}

void UCharacterBaseAttribute::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttribute, Mana, OldMana);
}

void UCharacterBaseAttribute::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttribute, MaxMana, OldMaxMana);
}
