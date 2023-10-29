// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"

UDefaultGameInstance::UDefaultGameInstance()
{
	//ConstructorHelpers::FObjectFinder<UClass> LUKRIEL(TEXT(""));
	ConstructorHelpers::FObjectFinder<UClass>  ALLIUM(TEXT("Class'/Game/Character/Allium/BP_Allium.BP_Allium_C'"));
	ConstructorHelpers::FObjectFinder<UClass>	RIANA(TEXT("Class'/Game/Character/Riana/BP_Riana.BP_Riana_C'"));
	ConstructorHelpers::FObjectFinder<UClass>	   LB(TEXT("Class'/Game/Character/Lb/BP_Lb.BP_Lb_C'"));

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/InputActions/InputMappingContext.InputMappingContext'"));
	if (!DEFAULT_CONTEXT.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("DEFAULT_CONTEXT load failed."));
		return;
	}

	PlayerInputMapping = DEFAULT_CONTEXT.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		IA_RUNESPELL1(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/RuneSpell1.RuneSpell1'")),
		IA_RUNESPELL2(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/RuneSpell2.RuneSpell2'")),
		IA_WARD(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Ward.Ward'")),
		IA_BOMB(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Bomb.Bomb'")),
		IA_OBJECTSELECT(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/ObjectSelect.ObjectSelect'")),
		IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Move.Move'"));

	if (!IA_RUNESPELL1.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_RUNESPELL1 load failed."));
		return;
	}
	if (!IA_RUNESPELL2.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_RUNESPELL2 load failed."));
		return;
	}
	if (!IA_WARD.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_WARD load failed."));
		return;
	}
	if (!IA_BOMB.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_BOMB load failed."));
		return;
	}
	if (!IA_OBJECTSELECT.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_OBJECTSELECT load failed."));
		return;
	}
	if (!IA_MOVE.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_MOVE load failed."));
		return;
	}

	RuneSpell1Action = IA_RUNESPELL1.Object;
	RuneSpell2Action = IA_RUNESPELL2.Object;
	WardAction = IA_WARD.Object;
	BombAction = IA_BOMB.Object;
	ObjectSelectAction = IA_OBJECTSELECT.Object;
	MoveAction = IA_MOVE.Object;

	if
		(
			//!LUKRIEL.Succeeded() ||
			!ALLIUM.Succeeded() ||
			!RIANA.Succeeded() ||
			!LB.Succeeded()
			)
	{
		UE_LOG(LogTemp, Error, TEXT("Blueprint asset load failed."));
		return;
	}

	BP_Characters[int(CharacterType::Lukriel)] = NULL;
	BP_Characters[int(CharacterType::Allium)] = ALLIUM.Object;
	BP_Characters[int(CharacterType::Riana)] = RIANA.Object;
	BP_Characters[int(CharacterType::Lb)] = LB.Object;
}

void UDefaultGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("UDefaultGameInstance Loaded"));
}
