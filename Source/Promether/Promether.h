// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDefaultAbilityID : uint8
{
	None			UMETA(DisplayName = "None"),
	Confirm			UMETA(DisplayName = "Confirm"),
	Cancel			UMETA(DisplayName = "Cancel"),
	BaseAttack		UMETA(DisplayName = "BaseAttack"),
	Skill1			UMETA(DisplayName = "Skill1"),
	Skill2			UMETA(DisplayName = "Skill2"),
	Skill3			UMETA(DisplayName = "Skill3"),
	Skill4			UMETA(DisplayName = "Skill4"),
	SIZE
};