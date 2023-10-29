// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"
#include "PlayerGeneric/DefaultPlayerState.h"
#include "PlayerGeneric/DefaultPlayerCharacter.h"

ADefaultAIController::ADefaultAIController()
{
	bWantsPlayerState = true;
}

void ADefaultAIController::OnPossess(APawn* aPawn)
{
	/* 
	* 
	* This was Stat initialize code. Depricated.

	//debug
	FString MyName = aPawn->GetName();

	ADefaultPlayerState* MyPlayerState = GetPlayerState<ADefaultPlayerState>();
	if (!MyPlayerState) return;

	ADefaultPlayerCharacter* ControlledPawn = Cast<ADefaultPlayerCharacter>(aPawn);
	if (!ControlledPawn) return;

	ControlledPawn->SetPlayerState(MyPlayerState);

	TArray<float> DefaultStatsValue;
	TArray<float> CooldownDurationValue;

	ControlledPawn->DefaultStats.GenerateValueArray(DefaultStatsValue);
	ControlledPawn->CooldownDuration.GenerateValueArray(CooldownDurationValue);

	MyPlayerState->InitPlayerStats(DefaultStatsValue, CooldownDurationValue);
	*/
}