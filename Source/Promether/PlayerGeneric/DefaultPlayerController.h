// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Net/UnrealNetwork.h"
#include "AIController.h"
#include "DefaultPlayerController.generated.h"

UCLASS()
class PROMETHER_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION(Server, Reliable)
	void Server_SpawnPlayerCamera();

	void SetACharacterOutlineColor(ACharacter* Target, bool Visible);

public:
	ADefaultPlayerController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void Skill1();
	void Skill2();
	void Skill3();
	void Skill4();
	void Skill4_End();
	void RuneSpell1();
	void RuneSpell2();
	void Ward();
	void Bomb();
	void ObjectSelect();
	void MoveTriggered();
	void MoveStarted();
	void Move();

	UFUNCTION(Server, Reliable)
	void MoveToLocation(FVector Location);

	FVector GetMouseHitLocation();

	UFUNCTION(BlueprintCallable, Category = "AI|Navigation")
	void SimpleMoveToLocation(AController* Controller, const FVector& Goal);

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &MovementResult);

	void Attack();

	UPROPERTY(BlueprintReadWrite)
	float MouseClickInterval;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> Skill1Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> Skill2Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> Skill3Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> Skill4Action;
	UPROPERTY(EditAnywhere, Category = "Input")
		TSoftObjectPtr<UInputAction> Skill4_EndAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RuneSpell1Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> RuneSpell2Action;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> WardAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> BombAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> ObjectSelectAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> MoveAction;
};
