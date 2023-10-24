// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROMETHER_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADefaultAIController();
	void OnPossess(APawn* aPawn) override;

};
