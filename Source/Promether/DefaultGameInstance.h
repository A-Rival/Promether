// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PrometherEnum.h"
#include "DefaultGameInstance.generated.h"

UCLASS()
class PROMETHER_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDefaultGameInstance();

	virtual void Init() override;

	UClass* GetCharacterBPRef(CharacterType Type) { return BP_Characters[(uint8)Type]; }

private:
	UPROPERTY()
	UClass* BP_Characters[(uint8)CharacterType::SIZE];
};
