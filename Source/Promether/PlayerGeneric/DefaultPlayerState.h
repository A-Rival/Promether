// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <iostream>
#include <map>

#include "../PrometherEnum.h"
#include "DefaultPlayerCharacter.h"
#include "../StatusEffect/StatusEffect.h"
#include "DefaultPlayerState.generated.h"

UCLASS()
class PROMETHER_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
					ADefaultPlayerState();
	void			GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void			InitPlayerStats(const TArray<float>& StatsValue, const TArray<float>& CooldownDurationValue);

	void			SetCharacterBPRef(UClass* Value)					{ CharacterBPRef = Value; }
	UClass*			GetCharacterBPRef()									const { return CharacterBPRef; }

	UFUNCTION(BlueprintCallable)
	void			SetTeam(TeamType Value)								{ Team = Value; }
	UFUNCTION(BlueprintCallable)
	TeamType		GetTeam()											const { return Team; }

	void			SetPlayerCamera(AActor* Actor)						{ PlayerCamera = Actor; }
	AActor*			GetPlayerCamera()									const { return PlayerCamera; }

	//fix later
	//UFUNCTION(BlueprintCallable)
	//void			SetCooldownDuration(CooldownType Key, float Value)	{ CooldownDuration[(uint8)Key] = Value; }
	//UFUNCTION(BlueprintCallable)
	//float			GetCooldownDuration(CooldownType Key)				const { return CooldownDuration[(uint8)Key]; }

	//Execute on server
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void			SetState(ECharacterState Value);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void			NetMulticast_SetState(ECharacterState Value);
	UFUNCTION(BlueprintCallable)
	ECharacterState GetState()											const { return State; }

	//Execute on server
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void			SetAttackType(CooldownType Value);
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void			NetMulticast_SetAttackType(CooldownType Value);
	UFUNCTION(BlueprintCallable)
	CooldownType	GetAttackType()										const { return AttackType; }

	UFUNCTION(BlueprintCallable)
	int32			GetCharacterLevel()									const;
	
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadWrite)
	TArray<float> Stats;
	UPROPERTY(Replicated, Transient, EditAnywhere, BlueprintReadWrite)
	TArray<float> MaxStats;

	UPROPERTY(Replicated, Transient, BlueprintReadWrite)
	TArray<float> CooldownDuration;
	UPROPERTY(Replicated, Transient, BlueprintReadWrite)
	TArray<float> MaxCooldownDuration;

private:
	UPROPERTY(Replicated, Transient)
	UClass*			CharacterBPRef;
	UPROPERTY(Replicated, Transient)
	TeamType		Team;

	UPROPERTY(Replicated, Transient)
	ECharacterState State;
	UPROPERTY(Replicated, Transient)
	CooldownType AttackType;

	//UPROPERTY(Replicated, Transient)
	//TMap<FUniqueObjectID, UStatusEffect> StatusEffectObject;

	UPROPERTY(Replicated, Transient)
	AActor* PlayerCamera;
};
