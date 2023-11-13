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

#include "DefaultPlayerState.h"
#include "DefaultPlayerCamera.h"



void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (!LocalPlayer) return;

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!InputSystem) return;

	if (PlayerInputMapping.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("AddMappingContext Failed"));
		return;
	}

	InputSystem->AddMappingContext(PlayerInputMapping.LoadSynchronous(), 0);
	this->bShowMouseCursor = true;
}

void ADefaultPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Server_SpawnPlayerCamera();

	AActor *PlayerCamera = GetPlayerState<ADefaultPlayerState>()->GetPlayerCamera();
	if (!PlayerCamera) 
	{
		UE_LOG(LogTemp, Error, TEXT("GetPlayerCamera Failed."));
		return;
	}

	SetViewTarget(PlayerCamera);

	UE_LOG(LogTemp, Warning, TEXT("SetViewTarget Success : %s"), *GetPlayerState<ADefaultPlayerState>()->GetPlayerCamera()->GetName());

	ADefaultPlayerCharacter* ControlledPawn = GetPawn<ADefaultPlayerCharacter>();
	if (!ControlledPawn) return;

	ADefaultPlayerState* MyPlayerState = GetPlayerState<ADefaultPlayerState>();
	if (!MyPlayerState) return;

	TArray<float> DefaultStatsValue;
	TArray<float> CooldownDurationValue;

	ControlledPawn->DefaultStats.GenerateValueArray(DefaultStatsValue);
	ControlledPawn->CooldownDuration.GenerateValueArray(CooldownDurationValue);

	MyPlayerState->InitPlayerStats(DefaultStatsValue, CooldownDurationValue);
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

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/InputActions/InputMappingContext.InputMappingContext'"));
	if (!DEFAULT_CONTEXT.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("DEFAULT_CONTEXT load failed."));
		return;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		IA_SKILL1(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Skill1.Skill1'")),
		IA_SKILL2(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Skill2.Skill2'")),
		IA_SKILL3(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Skill3.Skill3'")),
		IA_SKILL4(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Skill4.Skill4'")),
		IA_RUNESPELL1(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/RuneSpell1.RuneSpell1'")),
		IA_RUNESPELL2(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/RuneSpell2.RuneSpell2'")),
		IA_WARD(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Ward.Ward'")),
		IA_BOMB(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Bomb.Bomb'")),
		IA_OBJECTSELECT(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/ObjectSelect.ObjectSelect'")),
		IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/InputActions/Move.Move'"));

	if (!IA_SKILL1.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_SKILL1 load failed."));
		return;
	}
	if (!IA_SKILL2.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_SKILL2 load failed."));
		return;
	}
	if (!IA_SKILL3.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_SKILL3 load failed."));
		return;
	}
	if (!IA_SKILL4.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_ULTIMATESKILL load failed."));
		return;
	}
	if (!IA_RUNESPELL1.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_RUNESPELL1 load failed."));
		return;
	}
	if (!IA_RUNESPELL2.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_RUNESPELL2 load failed."));
		return;
	}
	if (!IA_WARD.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_WARD load failed."));
		return;
	}
	if (!IA_BOMB.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_BOMB load failed."));
		return;
	}
	if (!IA_OBJECTSELECT.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_OBJECTSELECT load failed."));
		return;
	}
	if (!IA_MOVE.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("IA_MOVE load failed."));
		return;
	}

	PlayerInputMapping = DEFAULT_CONTEXT.Object;
	Skill1Action = IA_SKILL1.Object;
	Skill2Action = IA_SKILL2.Object;
	Skill3Action = IA_SKILL3.Object;
	Skill4Action = IA_SKILL4.Object;
	RuneSpell1Action = IA_RUNESPELL1.Object;
	RuneSpell2Action = IA_RUNESPELL2.Object;
	WardAction = IA_WARD.Object;
	BombAction = IA_BOMB.Object;
	ObjectSelectAction = IA_OBJECTSELECT.Object;
	MoveAction = IA_MOVE.Object;
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

	EnhancedInputComponent->BindAction(Skill1Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Skill1);
	EnhancedInputComponent->BindAction(Skill2Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Skill2);
	EnhancedInputComponent->BindAction(Skill3Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Skill3);
	EnhancedInputComponent->BindAction(Skill4Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Skill4Triggered);
	EnhancedInputComponent->BindAction(Skill4Action.Get(), ETriggerEvent::Completed, this, &ADefaultPlayerController::Skill4Completed);
	EnhancedInputComponent->BindAction(RuneSpell1Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::RuneSpell1);
	EnhancedInputComponent->BindAction(RuneSpell2Action.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::RuneSpell2);
	EnhancedInputComponent->BindAction(WardAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Ward);
	EnhancedInputComponent->BindAction(BombAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Bomb);
	EnhancedInputComponent->BindAction(ObjectSelectAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::ObjectSelect);
	EnhancedInputComponent->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &ADefaultPlayerController::Move);
}

void ADefaultPlayerController::Skill1()
{
	if (GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] == 1)
		return;
	if (!(GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] >= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill1Cost]))
		return;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] -= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill1Cost];
	EndAttack();

	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] = 1;


	ACharacter* HitObject = nullptr;
	FVector Location = GetPawn()->GetActorLocation();
	Location.Z = 0;

	Server_StopMove();
	Multicast_StopMove();

	Multicast_SetRotation(GetMouseHitLocation());
	Server_SetRotation(GetMouseHitLocation());

	UE_LOG(LogTemp, Warning, TEXT("Skill1"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill1);
}

void ADefaultPlayerController::Skill2()
{
	if (GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] == 1)
		return;
	if (!(GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] >= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill2Cost]))
		return;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] -= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill2Cost];

	EndAttack();
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] = 1;
	ACharacter* HitObject = nullptr;
	FVector Location = GetPawn()->GetActorLocation();
	Location.Z = 0;

	Server_StopMove();
	Multicast_StopMove();

	Multicast_SetRotation(GetMouseHitLocation());
	Server_SetRotation(GetMouseHitLocation());

	UE_LOG(LogTemp, Warning, TEXT("Skill2"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill2);
}

void ADefaultPlayerController::Skill3()
{
	if (GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] == 1)
		return;
	if (!(GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] >= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill3Cost]))
		return;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] -= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill3Cost];
	EndAttack();
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] = 1;
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] = 1;

	ACharacter* HitObject = nullptr;
	FVector Location = GetPawn()->GetActorLocation();
	Location.Z = 0;

	Server_StopMove();
	Multicast_StopMove();

	Multicast_SetRotation(GetMouseHitLocation());
	Server_SetRotation(GetMouseHitLocation());

	UE_LOG(LogTemp, Warning, TEXT("Skill3"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill3);
}

void ADefaultPlayerController::Skill4Triggered()
{//��Ÿ�� üũ �ֱ�
	
   if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::charging] == 0)//������ true�� �ƴ� ��
	{
	   if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] == 0) {
		   GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Idle);
		   return;
	   }
		  
	   if (!(GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] >= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill4Cost])) {
		   GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Idle);
		   return;
	   }
		   
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Mana] -= GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skill4Cost];
	GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::charging] = 1;
	ACharacter* HitObject = nullptr;
	FVector Location = GetPawn()->GetActorLocation();
	//Location.Z = 0;

	Server_StopMove();
	Multicast_StopMove();

	Multicast_SetRotation(GetMouseHitLocation());
	Server_SetRotation(GetMouseHitLocation());

	UE_LOG(LogTemp, Warning, TEXT("Skill4 Triggered"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill4Triggered);

	}

   if (GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::charging] == 0) {
	   EndAttack();
	   GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] = 1;
	   GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Skillusable] = 1;
	   GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] = 1;

	   ACharacter* HitObject = nullptr;
	   FVector Location = GetPawn()->GetActorLocation();
	   //Location.Z = 0;

	   Server_StopMove();
	   Multicast_StopMove();

	   Multicast_SetRotation(GetMouseHitLocation());
	   Server_SetRotation(GetMouseHitLocation());

	   UE_LOG(LogTemp, Warning, TEXT("Skill4 Triggered"));
	   GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	   GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill4Triggered);

   }
}

void ADefaultPlayerController::Skill4Completed()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill4 Completed"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Skill4Comlpleted);
}

void ADefaultPlayerController::RuneSpell1()
{
	UE_LOG(LogTemp, Warning, TEXT("RuneSpell1"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::RuneSpell1);
}

void ADefaultPlayerController::RuneSpell2()
{
	UE_LOG(LogTemp, Warning, TEXT("RuneSpell2"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::RuneSpell2);
}

void ADefaultPlayerController::Ward()
{
	UE_LOG(LogTemp, Warning, TEXT("Ward"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Ward);
}

void ADefaultPlayerController::Bomb()
{
	UE_LOG(LogTemp, Warning, TEXT("Bomb"));
	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
	GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Bomb);
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
		Cast<ADefaultPlayerCharacter>(GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget()))
	{
		if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] == 0) return;
		BeginAttack();
	}
	else 
	{
		if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Movable] == 0)
			return;
		FVector Destination = GetMouseHitLocation();
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Moving);
		SimpleMoveToLocation(this, Destination);
		this->MoveToLocation(Destination);
	}
	
}

void ADefaultPlayerController::Multicast_SetRotation_Implementation(FVector MouseHitLocation)
{
	FVector Location = GetPawn()->GetActorLocation();
	Location.Z = 0;

	FRotator NewRotation = (MouseHitLocation - Location).Rotation();
	
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

	GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Idle);
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
	if (!GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats::Attackable] == 0)
		return;

	float MinDistance = GetPlayerState<ADefaultPlayerState>()->Stats[(uint8)EStats:: AttackRange];

	if (!GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget()) return;

	FVector Destination = GetPlayerState<ADefaultPlayerState>()->GetCurrentAttackTarget()->GetActorLocation(); // HitObject�� ��ġ�� �������� ����

	if (FVector::Dist(Destination, GetPawn()->GetActorLocation()) <= MinDistance)
	{
		if ((GetPlayerState<ADefaultPlayerState>()->CooldownDuration[(uint8)CooldownType::Attack] != 0))
			return;
		
		FVector Location = GetPawn()->GetActorLocation();
		Location.X = 0;

		Server_StopMove();
		Multicast_StopMove();

		Multicast_SetRotation(Destination);
		Server_SetRotation(Destination);

		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Attack);
		GetPlayerState<ADefaultPlayerState>()->SetAttackType(CooldownType::Attack);
	}
	else
	{
		GetPlayerState<ADefaultPlayerState>()->SetState(ECharacterState::Moving);
		SimpleMoveToLocation(this, Destination);
		this->MoveToLocation(Destination);
	}
}

void ADefaultPlayerController::MoveToLocation_Implementation(FVector Location)
{
	SimpleMoveToLocation(this, Location);
}
