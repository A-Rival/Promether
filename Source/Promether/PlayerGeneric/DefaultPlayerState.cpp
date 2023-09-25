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

void ADefaultPlayerState::InitPlayerStats()
{
	ADefaultPlayerCharacter* Initializer = Cast<ADefaultPlayerCharacter>(CharacterBPRef);

	Stats.Health									= Initializer->GetHealth();
	Stats.HPRegeneration							= Initializer->GetHPRegeneration();
	Stats.HealAndShieldpower						= Initializer->GetHealAndShieldpower();
	Stats.Armor										= Initializer->GetArmor();
	Stats.MagicResistance							= Initializer->GetMagicResistance();
	Stats.Tenacity									= Initializer->GetTenacity();
	Stats.SlowRisist								= Initializer->GetSlowRisist();
	Stats.AttackSpeed								= Initializer->GetAttackSpeed();
	Stats.AttackDamage								= Initializer->GetAttackDamage();
	Stats.AbilityPower								= Initializer->GetAbilityPower();
	Stats.CriticalStrikeChance						= Initializer->GetCriticalStrikeChance();
	Stats.CriticalStrikeDamage						= Initializer->GetCriticalStrikeDamage();
	Stats.ArmorPenetration							= Initializer->GetArmorPenetration();
	Stats.MagicPenetration							= Initializer->GetMagicPenetration();
	Stats.LifeSteal									= Initializer->GetLifeSteal();
	Stats.PhysicalVamp								= Initializer->GetPhysicalVamp();
	Stats.Omnivamp									= Initializer->GetOmnivamp();
	Stats.AbilityHaste								= Initializer->GetAbilityHaste();

	SetMultipleCooldownDuration(Initializer->GetCooldownDuration());

	Stats.Mana										= Initializer->GetMana();
	Stats.ManaRegeneration							= Initializer->GetManaRegeneration();
	Stats.Energy									= Initializer->GetEnergy();
	Stats.EnergyRegeneration						= Initializer->GetEnergyRegeneration();
	Stats.AttackRange								= Initializer->GetAttackRange();
	Stats.MovementSpeed								= Initializer->GetMovementSpeed();
	Stats.GoldGeneration							= Initializer->GetGoldGeneration();
	Stats.AttackDamageGrowth						= Initializer->GetAttackDamageGrowth();
	Stats.AttackSpeedGrowth							= Initializer->GetAttackSpeedGrowth();
	Stats.ArmorGrowth								= Initializer->GetArmorGrowth();
	Stats.MagicResistanceGrowth						= Initializer->GetMagicResistanceGrowth();
	Stats.HealthGrowth								= Initializer->GetHealthGrowth();
	Stats.HealthRegenerationGrowth					= Initializer->GetHealthRegenerationGrowth();
	Stats.ManaGrowth								= Initializer->GetManaGrowth();
	Stats.ManaRegenerationGrowth					= Initializer->GetManaRegenerationGrowth();
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
