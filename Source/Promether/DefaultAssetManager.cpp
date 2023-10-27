// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAssetManager.h"
#include "AbilitySystemGlobals.h"

void UDefaultAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
