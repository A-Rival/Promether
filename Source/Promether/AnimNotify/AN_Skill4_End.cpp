// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Skill4_End.h"

#include "../PlayerGeneric/DefaultPlayerCharacter.h"

void UAN_Skill4_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ADefaultPlayerCharacter* MyCharacter = MeshComp->GetOwner<ADefaultPlayerCharacter>();
	if (!MyCharacter) return;

	MyCharacter->Skill4_End();
}
