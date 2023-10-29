#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "../GAS/DefaultAbilitySystemComponent.h"
#include "../GAS/AttributeSet/CharacterBaseAttribute.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	CharacterBPRef = nullptr;

	AbilitySystemComponent = CreateDefaultSubobject<UDefaultAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Attribute = CreateDefaultSubobject<UCharacterBaseAttribute>(TEXT("Attribute"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	TeamTag = FGameplayTag::RequestGameplayTag(FName("Team.Neutral"));;
	EffectTag = FGameplayTag::RequestGameplayTag(FName("State.Return"));
}

void ADefaultPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADefaultPlayerState, CharacterBPRef);
	DOREPLIFETIME(ADefaultPlayerState, PlayerCamera);
	DOREPLIFETIME(ADefaultPlayerState, CurrentAttackTarget);
	DOREPLIFETIME(ADefaultPlayerState, PreviousAttackTarget);
}

UAbilitySystemComponent* ADefaultPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterBaseAttribute* ADefaultPlayerState::GetAttributeSet() const
{
	return Attribute;
}

bool ADefaultPlayerState::IsDead() const
{
	return GetHealth() < 0.0f;
}

void ADefaultPlayerState::ShowAbliityConfirmCancelText(bool ShowText)
{
	// TODO -- implement HUD
}

TeamType ADefaultPlayerState::GetTeam() const
{
	return TeamType::Null;
}

float ADefaultPlayerState::GetXP() const
{
	return Attribute->GetXP();
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

int32 ADefaultPlayerState::GetCharacterLevel() const
{
	return Attribute->GetXP() / 100.0f;
}

void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		TeamChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddUObject(this, &ADefaultPlayerState::TeamChanged);
		XPChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddUObject(this, &ADefaultPlayerState::XPChanged);
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddUObject(this, &ADefaultPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHealthAttribute()).AddUObject(this, &ADefaultPlayerState::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetManaAttribute()).AddUObject(this, &ADefaultPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxManaAttribute()).AddUObject(this, &ADefaultPlayerState::MaxManaChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(
			FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved
		).AddUObject(this, &ADefaultPlayerState::StunTagChanged);
	}
}

void ADefaultPlayerState::TeamChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("TeamChanged"));
}

void ADefaultPlayerState::XPChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("XPChanged"));
}

void ADefaultPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthChanged"));
}

void ADefaultPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxHealthChanged"));
}

void ADefaultPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("ManaChanged"));
}

void ADefaultPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxManaChanged"));
}

void ADefaultPlayerState::SetCurrentAttackTarget(AActor* Target)
{
	Server_SetCurrentAttackTarget(Target);
	Client_SetCurrentAttackTarget(Target);
}

void ADefaultPlayerState::SetPreviousAttackTarget(AActor* Target)
{
	Server_SetPreviousAttackTarget(Target);
	Client_SetPreviousAttackTarget(Target);
}

void ADefaultPlayerState::Server_SetCurrentAttackTarget_Implementation(AActor* Target)
{
	CurrentAttackTarget = Target;
}

void ADefaultPlayerState::Client_SetCurrentAttackTarget_Implementation(AActor* Target)
{
	CurrentAttackTarget = Target;
}

void ADefaultPlayerState::Server_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}

void ADefaultPlayerState::Client_SetPreviousAttackTarget_Implementation(AActor* Target)
{
	PreviousAttackTarget = Target;
}

void ADefaultPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
