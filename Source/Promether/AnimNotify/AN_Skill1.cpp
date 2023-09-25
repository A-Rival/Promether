// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Skill1.h"

#include "../PlayerGeneric/DefaultPlayerCharacter.h"

void UAN_Skill1::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (ADefaultPlayerCharacter* MyCharacter = MeshComp->GetOwner<ADefaultPlayerCharacter>())
	{
		if (AController* MyController = MyCharacter->GetController())
		{
			MyCharacter->Skill1();
		}
	}
}
