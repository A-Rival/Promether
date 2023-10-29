// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../DefaultAIController.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Promether/Promether.h"
#include "Promether/GAS/DefaultAbilitySystemComponent.h"
#include "Promether/GAS/AttributeSet/CharacterBaseAttribute.h"

ADefaultPlayerCharacter::ADefaultPlayerCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	TeamTag = FGameplayTag::RequestGameplayTag(FName("Team.Neutral"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("Status.Buff.Regenerate.Health"));

	bUseControllerRotationYaw = false;

	AIControllerClass = ADefaultAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-45.0f, 0.0f, 0.0f));
	CameraSpringArm->SetAbsolute(false, true, true);
	CameraSpringArm->TargetArmLength = 2000.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	CameraSpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

UAbilitySystemComponent* ADefaultPlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ADefaultPlayerCharacter::Tick(float DeltaTime)
{
	/*
	if (GetPlayerState<ADefaultPlayerState>())
	{
		if (!GPlayInEditorID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Server %s State : %d"), *GetName(), GetPlayerState<ADefaultPlayerState>()->GetState());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Client %d %s State : %d"), GPlayInEditorID, *GetName(), GetPlayerState<ADefaultPlayerState>()->GetState());
		}
	}
	*/
}

void ADefaultPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ADefaultPlayerState* State = GetPlayerState<ADefaultPlayerState>();
	if (!State) return;

	InitializeStartingValues(State);

	AddStartupEffects();
	AddCharacterAbilities();
}

bool ADefaultPlayerCharacter::IsDead() const
{
	return GetHealth() < 0.0f;
}

int32 ADefaultPlayerCharacter::GetAbilityLevel(EDefaultAbilityID AbilityID) const
{
	return 0;
}

void ADefaultPlayerCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
		return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);

	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void ADefaultPlayerCharacter::beginDead()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->Velocity = FVector(0);

	//OnCharacterDied.ExecuteIfBound(this);
	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);

		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}
}

void ADefaultPlayerCharacter::FinishDying()
{
}

float ADefaultPlayerCharacter::GetXP() const
{
	if (Attribute.IsValid())
		return Attribute->GetXP();

	return 0.0f;
}

float ADefaultPlayerCharacter::GetCalculatedLevel() const
{
	if (Attribute.IsValid())
		return Attribute->GetXP() / 100.0f; //fix later

	return 0.0f;
}

float ADefaultPlayerCharacter::GetHealth() const
{
	if (Attribute.IsValid())
		return Attribute->GetHealth();

	return 0.0f;
}

float ADefaultPlayerCharacter::GetMaxHealth() const
{
	if (Attribute.IsValid())
		return Attribute->GetMaxHealth();

	return 0.0f;
}

float ADefaultPlayerCharacter::GetMana() const
{
	if (Attribute.IsValid())
		return Attribute->GetMana();

	return 0.0f;
}

float ADefaultPlayerCharacter::GetMaxMana() const
{
	if (Attribute.IsValid())
		return Attribute->GetMaxMana();

	return 0.0f;
}

void ADefaultPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultPlayerCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
		return;

	for (TSubclassOf<UCharacterGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility( FGameplayAbilitySpec (
			StartupAbility,
			GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID),
			static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),
			this
		));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void ADefaultPlayerCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
		return;

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCalculatedLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void ADefaultPlayerCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffects : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffects, GetCalculatedLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void ADefaultPlayerCharacter::InitializeStartingValues(ADefaultPlayerState* State)
{
	if (!State) return;

	AbilitySystemComponent = Cast<UDefaultAbilitySystemComponent>(State->GetAbilitySystemComponent());
	State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, this);

	Attribute = State->GetAttributeSet();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());
}

void ADefaultPlayerCharacter::SetHealth(float Health)
{
	if (Attribute.IsValid())
		Attribute->SetHealth(Health);
}

void ADefaultPlayerCharacter::SetMana(float Mana)
{
	if (Attribute.IsValid())
		Attribute->SetHealth(Mana);
}

void ADefaultPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ADefaultPlayerState* State = GetPlayerState<ADefaultPlayerState>();
	if (!State) return;

	InitializeStartingValues(State);
	InitializeAttributes();
}
