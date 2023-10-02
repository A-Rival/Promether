// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PerformSkill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPerformSkill : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROMETHER_API IPerformSkill
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Skill4Started() = 0;
	virtual void Skill4Triggered() = 0;
	virtual void Skill4Completed() = 0;
};
