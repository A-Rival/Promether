#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	CharacterBPRef = nullptr;;
	Team = TeamType::Null;
	State = ECharacterState::Idle;
	InitPlayerStats();
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

void ADefaultPlayerState::InitPlayerStats()
{
	ADefaultPlayerCharacter* Initializer = Cast<ADefaultPlayerCharacter>(CharacterBPRef);

	Stats.Health									= Initializer->Health;
	Stats.HPRegeneration							= Initializer->HPRegeneration;
	Stats.HealAndShieldpower						= Initializer->HealAndShieldpower;
	Stats.Armor										= Initializer->Armor;
	Stats.MagicResistance							= Initializer->MagicResistance;
	Stats.Tenacity									= Initializer->Tenacity;
	Stats.SlowRisist								= Initializer->SlowRisist;
	Stats.AttackSpeed								= Initializer->AttackSpeed;
	Stats.AttackDamage								= Initializer->AttackDamage;
	Stats.AbilityPower								= Initializer->AbilityPower;
	Stats.CriticalStrikeChance						= Initializer->CriticalStrikeChance;
	Stats.CriticalStrikeDamage						= Initializer->CriticalStrikeDamage;
	Stats.ArmorPenetration							= Initializer->ArmorPenetration;
	Stats.MagicPenetration							= Initializer->MagicPenetration;
	Stats.LifeSteal									= Initializer->LifeSteal;
	Stats.PhysicalVamp								= Initializer->PhysicalVamp;
	Stats.Omnivamp									= Initializer->Omnivamp;
	Stats.AbilityHaste								= Initializer->AbilityHaste;

	SetMultipleCooldownDuration(Initializer->CooldownDuration);

	Stats.Mana										= Initializer->Mana;
	Stats.ManaRegeneration							= Initializer->ManaRegeneration;
	Stats.Energy									= Initializer->Energy;
	Stats.EnergyRegeneration						= Initializer->EnergyRegeneration;
	Stats.AttackRange								= Initializer->AttackRange;
	Stats.MovementSpeed								= Initializer->MovementSpeed;
	Stats.GoldGeneration							= Initializer->GoldGeneration;
	Stats.AttackDamageGrowth						= Initializer->AttackDamageGrowth;
	Stats.AttackSpeedGrowth							= Initializer->AttackSpeedGrowth;
	Stats.ArmorGrowth								= Initializer->ArmorGrowth;
	Stats.MagicResistanceGrowth						= Initializer->MagicResistanceGrowth;
	Stats.HealthGrowth								= Initializer->HealthGrowth;
	Stats.HealthRegenerationGrowth					= Initializer->HealthRegenerationGrowth;
	Stats.ManaGrowth								= Initializer->ManaGrowth;
	Stats.ManaRegenerationGrowth					= Initializer->ManaRegenerationGrowth;
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

void ADefaultPlayerState::SetMultipleCooldownDuration(const float* Value)
{
	std::memcpy(&CooldownDuration, Value, sizeof(float) * (uint8)CooldownType::SIZE);
}
