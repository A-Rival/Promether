// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DefaultPlayerCamera.generated.h"

UCLASS()
class PROMETHER_API ADefaultPlayerCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefaultPlayerCamera(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
