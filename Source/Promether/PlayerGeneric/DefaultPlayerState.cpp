#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	CharacterBPRef = nullptr;;
	Team = TeamType::Null;
	State = ECharacterState::Idle;

	NetUpdateFrequency = 100.0f;
}

void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerState, CharacterBPRef);
	DOREPLIFETIME(ADefaultPlayerState, Team);

	DOREPLIFETIME(ADefaultPlayerState, CooldownDuration);
	DOREPLIFETIME(ADefaultPlayerState, MaxCooldownDuration);

	DOREPLIFETIME(ADefaultPlayerState, Stats);
	DOREPLIFETIME(ADefaultPlayerState, MaxStats);

	DOREPLIFETIME(ADefaultPlayerState, State);
	DOREPLIFETIME(ADefaultPlayerState, AttackType);
	DOREPLIFETIME(ADefaultPlayerState, PlayerCamera);

	DOREPLIFETIME(ADefaultPlayerState, CurrentAttackTarget);
	DOREPLIFETIME(ADefaultPlayerState, PreviousAttackTarget);
}

void ADefaultPlayerState::InitPlayerStats_Implementation(const TArray<float>& StatsValue, const TArray<float>& CooldownDurationValue)
{
	MaxStats.Append(StatsValue);
	Stats.Append(StatsValue);
	CooldownDuration.Append(CooldownDurationValue);

	for (float Value : CooldownDurationValue)
	{
		MaxCooldownDuration.Add(0.0f);
	}

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

void ADefaultPlayerState::SetCurrentAttackTarget(AActor* Target)
{
	Server_SetCurrentAttackTarget(Target);
	Client_SetCurrentAttackTarget(Target);
}

void ADefaultPlayerState::Server_SetCurrentAttackTarget_Implementation(AActor* Target)
{
	CurrentAttackTarget = Target;
}

void ADefaultPlayerState::Client_SetCurrentAttackTarget_Implementation(AActor* Target)
{
	CurrentAttackTarget = Target;
}

void ADefaultPlayerState::SetPreviousAttackTarget(AActor* Target)
{
	Server_SetPreviousAttackTarget(Target);
	Client_SetPreviousAttackTarget(Target);
}

void ADefaultPlayerState::Server_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}

void ADefaultPlayerState::Client_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}
