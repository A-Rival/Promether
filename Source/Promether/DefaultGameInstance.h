// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PrometherEnum.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "DefaultGameInstance.generated.h"

UCLASS()
class PROMETHER_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDefaultGameInstance();

	virtual void Init() override;

	UClass* GetCharacterBPRef(CharacterType Type) { return BP_Characters[(uint8)Type]; }

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RuneSpell1Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RuneSpell2Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> WardAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> BombAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> ObjectSelectAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> MoveAction;

private:
	UPROPERTY()
	UClass* BP_Characters[(uint8)CharacterType::SIZE];
};
