// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerCamera.h"

ADefaultPlayerCamera::ADefaultPlayerCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 0.0f, 0.0f));
	CameraSpringArm->SetAbsolute(false, true, true);
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	SetRootComponent(CameraSpringArm);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called every frame
void ADefaultPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

