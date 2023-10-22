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

}
