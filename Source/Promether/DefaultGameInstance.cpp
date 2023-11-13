// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"

UDefaultGameInstance::UDefaultGameInstance()
{
	//ConstructorHelpers::FObjectFinder<UClass> LUKRIEL(TEXT(""));
	ConstructorHelpers::FObjectFinder<UClass>  ALLIUM(TEXT("Class'/Game/Character/Allium/BP_Allium.BP_Allium_C'"));
	ConstructorHelpers::FObjectFinder<UClass>	RIANA(TEXT("Class'/Game/Character/Riana/BP_Riana.BP_Riana_C'"));
	ConstructorHelpers::FObjectFinder<UClass>	   LB(TEXT("Class'/Game/Character/Lb/BP_Lb.BP_Lb_C'"));

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
