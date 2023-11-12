// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_AnimEnd.h"

#include "../PlayerGeneric/DefaultPlayerCharacter.h"
#include "../PlayerGeneric/DefaultPlayerState.h"


void UAN_AnimEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	ADefaultPlayerCharacter* MyCharacter = MeshComp->GetOwner<ADefaultPlayerCharacter>();
	if (!MyCharacter) return;

	ADefaultPlayerState* MyState = MyCharacter->GetPlayerState<ADefaultPlayerState>();
	if (!MyState) return;
	MyState->SetState(ECharacterState::Idle); 
	UE_LOG(LogTemp, Warning, TEXT("State log : %d"), MyState->GetState());
	MyState->Stats[(uint8)EStats::Attackable] = 0;
	MyState->Stats[(uint8)EStats::Skillusable] = 0;
	MyState->Stats[(uint8)EStats::Movable] = 0;
	

}
