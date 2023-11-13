#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	CharacterBPRef = nullptr;;
	Team = TeamType::Null;
	State = ECharacterState::Idle;
}

void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerState, CharacterBPRef);
	DOREPLIFETIME(ADefaultPlayerState, Team);

	DOREPLIFETIME(ADefaultPlayerState, CooldownDuration);

	DOREPLIFETIME(ADefaultPlayerState, Stats);
	DOREPLIFETIME(ADefaultPlayerState, MaxStats);

	DOREPLIFETIME(ADefaultPlayerState, State);
	DOREPLIFETIME(ADefaultPlayerState, AttackType);
	//DOREPLIFETIME(ADefaultPlayerState, StatusEffectObject);
	DOREPLIFETIME(ADefaultPlayerState, PlayerCamera);
}

void ADefaultPlayerState::InitPlayerStats_Implementation(const TArray<float>& StatsValue, const TArray<float>& CooldownDurationValue)
{
	MaxStats.Append(StatsValue);
	Stats.Append(StatsValue);
	CooldownDuration.Append(CooldownDurationValue);
	MaxCooldownDuration.Append(CooldownDurationValue);


	for (float Value : StatsValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Values: %f"), Value);
	}
}

void ADefaultPlayerState::NetMulticast_SetAttackType_Implementation(CooldownType Value)
{
	AttackType = Value;
}

void ADefaultPlayerState::NetMulticast_SetState_Implementation(ECharacterState Value)
{
	State = Value;
}

void ADefaultPlayerState::SetState_Implementation(ECharacterState Value)
{
	NetMulticast_SetState(Value);
}

void ADefaultPlayerState::SetAttackType_Implementation(CooldownType Value)
{
	NetMulticast_SetAttackType(Value);
}

int32 ADefaultPlayerState::GetCharacterLevel() const
{
	return int32();
}
