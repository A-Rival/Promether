#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "../GAS/DefaultAbilitySystemComponent.h"
#include "../GAS/AttributeSet/CharacterBaseAttribute.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	CharacterBPRef = nullptr;
	Team = TeamType::Null;
	State = ECharacterState::Idle;

	AbilitySystemComponent = CreateDefaultSubobject<UDefaultAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attribute = CreateDefaultSubobject<UCharacterBaseAttribute>(TEXT("Attribute"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectTag = FGameplayTag::RequestGameplayTag(FName("State.EffectTag"));
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
	DOREPLIFETIME(ADefaultPlayerState, PlayerCamera);

	DOREPLIFETIME(ADefaultPlayerState, CurrentAttackTarget);
	DOREPLIFETIME(ADefaultPlayerState, PreviousAttackTarget);
}

UAbilitySystemComponent* ADefaultPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ADefaultPlayerState::GetHealth() const
{
	return Attribute->GetHealth();
}

float ADefaultPlayerState::GetMaxHealth() const
{
	return Attribute->GetMaxHealth();
}

float ADefaultPlayerState::GetMana() const
{
	return Attribute->GetMana();
}

float ADefaultPlayerState::GetMaxMana() const
{
	return Attribute->GetMaxMana();
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

void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddUObject(this, &ADefaultPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHealthAttribute()).AddUObject(this, &ADefaultPlayerState::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetManaAttribute()).AddUObject(this, &ADefaultPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxManaAttribute()).AddUObject(this, &ADefaultPlayerState::MaxManaChanged);

		//AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::Request)
	}
}

void ADefaultPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADefaultPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADefaultPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
}

void ADefaultPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
}

void ADefaultPlayerState::Server_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}

void ADefaultPlayerState::Client_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}
