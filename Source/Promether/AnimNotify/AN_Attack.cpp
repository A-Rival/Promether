// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Attack.h"
#include "GameFramework/Controller.h"

#include "../PlayerGeneric/DefaultPlayerCharacter.h"

void UAN_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (ADefaultPlayerCharacter* MyCharacter = MeshComp->GetOwner<ADefaultPlayerCharacter>())
	{
		if (AController* MyController = MyCharacter->GetController())
		{
			MyCharacter->Attack();
		}
	}
}