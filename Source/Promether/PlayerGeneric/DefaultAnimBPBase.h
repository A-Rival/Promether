// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../PrometherEnum.h"
#include "DefaultAnimBPBase.generated.h"

UCLASS()
class PROMETHER_API UDefaultAnimBPBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UDefaultAnimBPBase();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(Transient, BlueprintReadWrite)
	ECharacterState State;

	UPROPERTY(Transient, BlueprintReadWrite)
	CooldownType AttackType;
};
