// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDefaultAbilityID : uint8
{
	None			UMETA(DisplayName = "None"),
	BaseAttack		UMETA(DisplayName = "BaseAttack"),
	Skill1			UMETA(DisplayName = "Skill1"),
	Skill2			UMETA(DisplayName = "Skill2"),
	Skill3			UMETA(DisplayName = "Skill3"),
	Skill4			UMETA(DisplayName = "Skill4"),
	RuneSpell1		UMETA(DisplayName = "RuneSpell1"),
	RuneSpell2		UMETA(DisplayName = "RuneSpell2"),
	Ward			UMETA(DisplayName = "Ward"),
	Bomb			UMETA(DisplayName = "Bomb"),
	SIZE
};