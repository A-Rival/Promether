// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAbilitySystemComponent.h"

void UDefaultAbilitySystemComponent::ReceiveDamage(UDefaultAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.ExecuteIfBound(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
