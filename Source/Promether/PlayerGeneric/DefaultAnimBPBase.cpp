// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultAnimBPBase.h"

#include "DefaultPlayerState.h"

UDefaultAnimBPBase::UDefaultAnimBPBase()
{
	State = ECharacterState::Idle;
}

void UDefaultAnimBPBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (APawn* MyPawn = TryGetPawnOwner())
	{
		if (ADefaultPlayerState* MyPlayerState = MyPawn->GetPlayerState<ADefaultPlayerState>())
		{
			State = MyPlayerState->GetState();
			AttackType = MyPlayerState->GetAttackType();

			/*
			if (!GPlayInEditorID)
			{
				UE_LOG(LogTemp, Warning, TEXT("Server %s State : %d"), *MyPawn->GetName(), State);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Client %d %s State : %d"), GPlayInEditorID, *MyPawn->GetName(), State);
			}
			*/
		}
	}
}
