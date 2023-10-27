// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DefaultAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FReceivedDamageDelegate, UDefaultAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

UCLASS()
class PROMETHER_API UDefaultAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(UDefaultAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);

};
