// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Skill2.h"

#include "../PlayerGeneric/DefaultPlayerCharacter.h"

void UAN_Skill2::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ADefaultPlayerCharacter* MyCharacter = MeshComp->GetOwner<ADefaultPlayerCharacter>();
	if (!MyCharacter) return; 
	
	MyCharacter->Skill2();
}
