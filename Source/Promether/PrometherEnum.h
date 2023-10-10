#pragma once
#include "CoreMinimal.h"

#include "DamageType/BaseAttack.h"
#include "DefaultStats.h"

UENUM(BlueprintType)
enum class CharacterType : uint8
{
	Lukriel,
	Allium,
	Riana,
	Lb,
	SIZE
};

/*UENUM »ç¿ë¹ý
if (const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("CharacterType"), true))
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CharStateEnum->GetNameByValue((uint8)Type).ToString());
}
*/

UENUM(BlueprintType)
enum class TeamType : uint8
{
	Null,
	Neutral,
	Black,
	White
};

UENUM(BlueprintType)
enum class CooldownType : uint8
{
	Skill1,
	Skill2,
	Skill3,
	Skill4Started,
	Skill4Triggered,
	Skill4Comlpleted,
	RuneSpell1,
	RuneSpell2,
	Ward,
	Bomb,
	Move,
	Attack,
	SIZE
};

enum class CCType : uint32
{
	None			= 0x00000000,
	Slow			= 0x00000001,
	Cripple			= 0x00000002,
	Silence			= 0x00000004,
	Blind			= 0x00000008,
	BlockedSight	= 0x00000010,
	Grounding		= 0x00000020,
	Polymorph		= 0x00000040,
	Disarmed		= 0x00000080,
	Kinematic		= 0x00000100,
	Knockdown		= 0x00000200,
	Root			= 0x00000400,
	Stun			= 0x00000800,
	Airbone			= 0x00001000,
	Knockback		= 0x00002000,
	Grab			= 0x00004000,
	Suspension		= 0x00008000,
	Taunt			= 0x00010000,
	Charm			= 0x00020000,
	Flee			= 0x00040000,
	Suppressed		= 0x00080000,
	Banishment		= 0x00100000,
	Sleep			= 0x00200000
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Moving,
	Attack,
	Dead,
	SIZE
};

struct FUniqueObjectID
{
	double ConstructTime;
	int32 RandomUniqueNumber;
};

UENUM(BlueprintType)
enum class EStats : uint8
{
	Health,
	HPRegeneration,
	HealAndShieldpower, 
	Armor,
	MagicResistance,
	Tenacity,
	SlowRisist,
	AttackSpeed,
	AttackDamage,
	AbilityPower,
	CriticalStrikeChance,
	CriticalStrikeDamage,
	ArmorPenetration,
	MagicPenetration,
	LifeSteal,
	PhysicalVamp,
	Omnivamp,
	AbilityHaste,
	Mana,
	ManaRegeneration,
	Energy,
	EnergyRegeneration,
	AttackRange,
	MovementSpeed,
	GoldGeneration,
	AttackDamageGrowth,
	AttackSpeedGrowth,
	ArmorGrowth,
	MagicResistanceGrowth,
	HealthGrowth,
	HealthRegenerationGrowth,
	ManaGrowth,
	ManaRegenerationGrowth,
	Skill1Cost,
	Skill2Cost,
	Skill3Cost,
	Skill4Cost,
	SIZE
};