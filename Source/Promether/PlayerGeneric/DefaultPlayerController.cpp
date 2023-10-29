// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"


#include "../DefaultGameInstance.h"
#include "DefaultPlayerState.h"
#include "DefaultPlayerCharacter.h"
#include "DefaultPlayerCamera.h"
#include "../Promether.h"



void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (!LocalPlayer) return;

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!InputSystem) return;

	UDefaultGameInstance* Instance = GetGameInstance<UDefaultGameInstance>();
	if (!Instance) return;

	InputSystem->AddMappingContext(Instance->PlayerInputMapping.LoadSynchronous(), 0);
	this->bShowMouseCursor = true;
}

void ADefaultPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Server_SpawnPlayerCamera();

	ADefaultPlayerState* State = GetPlayerState<ADefaultPlayerState>();
	if (!State) return;

	AActor *PlayerCamera = State->GetPlayerCamera();
	if (!PlayerCamera) 
	{
		UE_LOG(LogTemp, Error, TEXT("GetPlayerCamera Failed."));
		return;
	}

	SetViewTarget(PlayerCamera);

	UE_LOG(LogTemp, Warning, TEXT("SetViewTarget Success : %s"), *State->GetPlayerCamera()->GetName());

	State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, aPawn);
	/*
	*
	* This was Stat initialize code. Depricated.

	ADefaultPlayerCharacter* ControlledPawn = GetPawn<ADefaultPlayerCharacter>();
	if (!ControlledPawn) return;

	ADefaultPlayerState* MyPlayerState = GetPlayerState<ADefaultPlayerState>();
	if (!MyPlayerState) return;

	TArray<float> DefaultStatsValue;
	TArray<float> CooldownDurationValue;

	ControlledPawn->DefaultStats.GenerateValueArray(DefaultStatsValue);
	ControlledPawn->CooldownDuration.GenerateValueArray(CooldownDurationValue);

	MyPlayerState->InitPlayerStats(DefaultStatsValue, CooldownDurationValue);
	*/
}

void ADefaultPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ADefaultPlayerController::Server_SpawnPlayerCamera_Implementation()
{
	AActor* OutContextPlayerCamera = nullptr;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;

	UE_LOG(LogTemp, Warning, TEXT("SpawnPlayerCamera"));

	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	FTransform SpawnTransform = FTransform();

	SpawnTransform.SetLocation(MyPawn->GetActorLocation());

	OutContextPlayerCamera = GetWorld()->SpawnActor<AActor>(ADefaultPlayerCamera::StaticClass(), SpawnTransform, SpawnInfo);
	if (!OutContextPlayerCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("Camera Spawn Failed."));
		return;
	}
	
	GetPlayerState<ADefaultPlayerState>()->SetPlayerCamera(OutContextPlayerCamera);
	OutContextPlayerCamera->AttachToActor(GetPawn(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));

	UE_LOG(LogTemp, Warning, TEXT("SetPlayerCamera Success : %s, %d"), *GetPlayerState<ADefaultPlayerState>()->GetPlayerCamera()->GetName(), GetPlayerState<ADefaultPlayerState>()->GetPlayerCamera());
}

void ADefaultPlayerController::SetACharacterOutlineColor(ACharacter* Target, bool Visible)
{
	if (!Target) return;

	ADefaultPlayerState* State = Target->GetPlayerState<ADefaultPlayerState>();
	if (!State)
	{
		UE_LOG(LogTemp, Error, TEXT("GetPlayerState<ADefaultPlayerState> Failed"));
		return;
	}

	if (State->GetTeam() == GetPlayerState<ADefaultPlayerState>()->GetTeam())
	{
		Target->GetMesh()->SetRenderCustomDepth(Visible);
		Target->GetMesh()->CustomDepthStencilValue = 1;
	}
	else
	{
		Target->GetMesh()->SetRenderCustomDepth(Visible);
		Target->GetMesh()->CustomDepthStencilValue = 2;
	}
}

ADefaultPlayerController::ADefaultPlayerController()
{
	MouseClickInterval = 0.2;

	PrimaryActorTick.bCanEverTick = true;
	AutoManageActiveCameraTarget(false);

	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADefaultPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;

	UDefaultGameInstance* Instance = GetGameInstance<UDefaultGameInstance>();
	if (!Instance) return;
	
	EnhancedInputComponent->BindAction(Instance->RuneSpell1Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::RuneSpell1);
	EnhancedInputComponent->BindAction(Instance->RuneSpell2Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::RuneSpell2);
	EnhancedInputComponent->BindAction(Instance->WardAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Ward);
	EnhancedInputComponent->BindAction(Instance->BombAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Bomb);
	EnhancedInputComponent->BindAction(Instance->ObjectSelectAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::ObjectSelect);
	EnhancedInputComponent->BindAction(Instance->MoveAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Move);
}

void ADefaultPlayerController::RuneSpell1()
{
	UE_LOG(LogTemp, Warning, TEXT("RuneSpell1"));
}

void ADefaultPlayerController::RuneSpell2()
{
	UE_LOG(LogTemp, Warning, TEXT("RuneSpell2"));
}

void ADefaultPlayerController::Ward()
{
	UE_LOG(LogTemp, Warning, TEXT("Ward"));
}

void ADefaultPlayerController::Bomb()
{
	UE_LOG(LogTemp, Warning, TEXT("Bomb"));
}

void ADefaultPlayerController::ObjectSelect()
{
	ADefaultPlayerState* State = GetPlayerState<ADefaultPlayerState>();
	if (!State) return;

	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);

	ACharacter* HitObject = Cast<ACharacter>(HitResult.GetActor());

	if (!HitObject)
	{
		SetACharacterOutlineColor(Cast<ACharacter>(State->GetPreviousAttackTarget()), false);
		State->SetPreviousAttackTarget(nullptr);
		State->SetCurrentAttackTarget(nullptr);
		return;
	}

	if (State->GetPreviousAttackTarget() != HitResult.GetActor())
	{
		SetACharacterOutlineColor(Cast<ACharacter>(State->GetPreviousAttackTarget()), false);

		State->SetPreviousAttackTarget(HitResult.GetActor());
		State->SetCurrentAttackTarget(HitResult.GetActor());

		SetACharacterOutlineColor(HitObject, true);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *State->GetCurrentAttackTarget()->GetName());

	FString Name = HitResult.GetActor()->GetName();
	APlayerState* TargetState = Cast<APawn>(HitResult.GetActor())->GetPlayerState();
}

void ADefaultPlayerController::Move()
{
	EndAttack();
	ObjectSelect();
	
	if (GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget() != GetPawn<AActor>() &&
		Cast<ADefaultPlayerCharacter>(GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget())) //본인이 아니고 공격이 가능한 대상(적이든 아군이든)일 때
	{
		//if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] == 0) return;
		BeginAttack(); //HitObject를 대상으로 BeginAttack 실행
	}
	else 
	{
		//if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] == 0)
		//	return;
		FVector Destination = GetMouseHitLocation();
		// TODO - animation state update fix
		/*
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Moving);
		*/
		SimpleMoveToLocation(this, Destination);
		this->MoveToLocation(Destination);
	}
	
}

void ADefaultPlayerController::Multicast_SetRotation_Implementation(FVector MouseHitLocation)
{
	FVector Location = GetPawn()->GetActorLocation();
	Location.Z = 0;

	FRotator NewRotation = (MouseHitLocation - Location).Rotation();

	// 만약 X축을 고정하고 싶다면 아래와 같이 해당 값을 설정합니다.
	
	NewRotation.Pitch = 0;

	GetPawn()->SetActorRotation(NewRotation);
	
}

void ADefaultPlayerController::Server_SetRotation_Implementation(FVector MouseHitLocation)
{
	Multicast_SetRotation(MouseHitLocation);
}

void ADefaultPlayerController::Server_StopMove_Implementation()
{
	Multicast_StopMove();
}

void ADefaultPlayerController::Multicast_StopMove_Implementation()
{
	UPathFollowingComponent* PFollowComp = this->FindComponentByClass<UPathFollowingComponent>();
	if (!PFollowComp) return;

	PFollowComp->OnRequestFinished.Clear();

	PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);

	PFollowComp->OnRequestFinished.AddUObject(this, &ADefaultPlayerController::OnMoveCompleted);
}

FVector ADefaultPlayerController::GetMouseHitLocation()
{
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);
	HitResult.Location.Z = 0;

	//UE_LOG(LogTemp, Warning, TEXT("Client%d MoveTo : (%f, %f)"), GPlayInEditorID, HitResult.Location.X, HitResult.Location.Y);

	FVector ActorLocation = GetPawn()->GetActorLocation();
	ActorLocation.Z = 0;

	float CapsuleRadius = GetPawn<ACharacter>()->GetCapsuleComponent()->GetScaledCapsuleRadius();

	FVector Destination = (HitResult.Location - ActorLocation).GetSafeNormal() * CapsuleRadius + HitResult.Location;

	DrawDebugLine(GetWorld(), ActorLocation, HitResult.Location, FColor::Blue, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), HitResult.Location, Destination, FColor::Emerald, false, 1, 0, 1);

	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld) return Destination;

	FHitResult CollisionCheck;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());

	FVector Start = HitResult.Location;
	FVector End = Destination;

	if (!CurrentWorld->LineTraceSingleByChannel(CollisionCheck, Start, End, ECC_Visibility, CollisionParams))
		return Destination;

	DrawDebugLine(CurrentWorld, Start, End, FColor::Red, false, 1.5, 0, 2);
	Destination = HitResult.Location;

	return Destination;
}

void ADefaultPlayerController::SimpleMoveToLocation(AController* Controller, const FVector& GoalLocation)
{
	UNavigationSystemV1* NavSys = Controller ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld()) : nullptr;
	if (NavSys == nullptr || Controller == nullptr || Controller->GetPawn() == nullptr)
	{
		UE_LOG(LogNavigation, Warning, TEXT("UNavigationSystemV1::SimpleMoveToActor called for NavSys:%s Controller:%s controlling Pawn:%s (if any of these is None then there's your problem"),
			*GetNameSafe(NavSys), *GetNameSafe(Controller), Controller ? *GetNameSafe(Controller->GetPawn()) : TEXT("NULL"));
		return;
	}

	AAIController* AsAIController = Cast<AAIController>(Controller);
	UPathFollowingComponent* PFollowComp = nullptr;

	if (AsAIController)
	{
		PFollowComp = AsAIController->GetPathFollowingComponent();
	}
	else
	{
		PFollowComp = Controller->FindComponentByClass<UPathFollowingComponent>();
		if (PFollowComp == nullptr)
		{
			PFollowComp = NewObject<UPathFollowingComponent>(Controller);
			PFollowComp->RegisterComponentWithWorld(Controller->GetWorld());
			PFollowComp->Initialize();
			PFollowComp->OnRequestFinished.AddUObject(this, &ADefaultPlayerController::OnMoveCompleted);
		}
	}

	if (PFollowComp == nullptr)
	{
		return;
	}

	if (!PFollowComp->IsPathFollowingAllowed())
	{
		return;
	}

	const bool bAlreadyAtGoal = PFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest, bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
	}

	if (bAlreadyAtGoal)
	{
		PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
	}
	else
	{
		const FVector AgentNavLocation = Controller->GetNavAgentLocation();
		const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef(), AgentNavLocation);
		if (NavData)
		{
			FPathFindingQuery Query(Controller, *NavData, AgentNavLocation, GoalLocation);
			FPathFindingResult Result = NavSys->FindPathSync(Query);
			if (Result.IsSuccessful())
			{
				PFollowComp->RequestMove(FAIMoveRequest(GoalLocation), Result.Path);
			}
			else if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
			}
		}
	}
}

void ADefaultPlayerController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& MovementResult)
{
	if (!MovementResult.IsSuccess()) return;

	if (!GPlayInEditorID)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server MoveCompleted"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Client%d MoveCompleted"), GPlayInEditorID);
	}

	// TODO - animation state update fix
	/*
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Idle);
	*/
}

void ADefaultPlayerController::BeginAttack()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefaultPlayerController::RepeatedAttack, 0.1f, true);
}

void ADefaultPlayerController::EndAttack()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ADefaultPlayerController::RepeatedAttack()
{
	Attack();
}

void ADefaultPlayerController::Attack()
{
	//if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] == 0)
	//	return;

	//float MinDistance = GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats:: AttackRange];

	if (!GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget()) return;

	FVector Destination = GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget()->GetActorLocation(); // HitObject의 위치를 목적지로 설정

	if (/*FVector::Dist(Destination, GetPawn()->GetActorLocation()) <= MinDistance*/ true)
	{
		//if ((GetPlayerState<ADefaultPlayerState>()->CooldownDuration[(uint8)CooldownType::Attack] != 0))
		//	return;
		
		FVector Location = GetPawn()->GetActorLocation();
		Location.X = 0;

		Server_StopMove();
		Multicast_StopMove();

		Multicast_SetRotation(Destination);
		Server_SetRotation(Destination);

		// TODO - animation state update fix
		/*
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
		GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Attack);
		*/
	}
	else
	{
		// TODO - animation state update fix
		/*
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Moving);
		*/
		SimpleMoveToLocation(this, Destination);
		this->MoveToLocation(Destination);
	}
}

void ADefaultPlayerController::MoveToLocation_Implementation(FVector Location)
{
	SimpleMoveToLocation(this, Location);
}
