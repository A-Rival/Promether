// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/PlayerStartPIE.h"
#include "EngineUtils.h"

#include "../PrometherEnum.h"
#include "../PlayerGeneric/DefaultPlayerController.h"
#include "../DefaultGameInstance.h"
#include "../PlayerGeneric/DefaultPlayerState.h"
#include "../DefaultGameStateBase.h"
#include "../PlayerGeneric/DefaultPlayerCamera.h"

ADeathmatch::ADeathmatch()
{
	PrimaryActorTick.bCanEverTick = true;

	//DefaultPawnClass = AActor::StaticClass();
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();
	GameStateClass = ADefaultGameStateBase::StaticClass();
}

void ADeathmatch::Tick(float DeltaSeconds)
{
	/*
	UWorld* World = GetWorld();
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		if (AController* Con = It->GetInstigatorController())
		{
			if (APlayerState* Sta = Con->GetPlayerState<APlayerState>())
			{
				if (ADefaultPlayerState* MyState = Cast<ADefaultPlayerState>(Sta))
				{
					UE_LOG(LogTemp, Warning, TEXT("Server %s State = %d"), *It->GetName(), MyState->GetState());
				}
			}
		}
	}
	*/
}

AActor* ADeathmatch::ChoosePlayerStart_Implementation(AController* Player)
{
	// Choose a player start
	APlayerStart* FoundPlayerStart = nullptr;

	UClass* PawnClass = nullptr;
	if (ADefaultPlayerState* NewPlayerState = Player->GetPlayerState<ADefaultPlayerState>())
	{
		PawnClass = NewPlayerState->GetCharacterBPRef();
	}

	APawn* PawnToFit = PawnClass ? PawnClass->GetDefaultObject<APawn>() : nullptr;
	TArray<APlayerStart*> UnOccupiedStartPoints;
	TArray<APlayerStart*> OccupiedStartPoints;
	UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			FoundPlayerStart = PlayerStart;
			break;
		}
		else
		{
			FVector ActorLocation = PlayerStart->GetActorLocation();
			const FRotator ActorRotation = PlayerStart->GetActorRotation();
			if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
			{
				UnOccupiedStartPoints.Add(PlayerStart);
			}
			else if (World->FindTeleportSpot(PawnToFit, ActorLocation, ActorRotation))
			{
				OccupiedStartPoints.Add(PlayerStart);
			}
		}
	}
	if (FoundPlayerStart == nullptr)
	{
		if (UnOccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];
		}
		else if (OccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = OccupiedStartPoints[FMath::RandRange(0, OccupiedStartPoints.Num() - 1)];
		}
	}

	return FoundPlayerStart;
}

APawn* ADeathmatch::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save default player pawns into a map

	UClass* PawnClass = nullptr;
	if (ADefaultPlayerState* NewPlayerState = NewPlayer->GetPlayerState<ADefaultPlayerState>())
	{
		PawnClass = NewPlayerState->GetCharacterBPRef();
	}

	APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo);
	if (!ResultPawn)
	{
		UE_LOG(LogGameMode, Warning, TEXT("SpawnDefaultPawnAtTransform: Couldn't spawn Pawn of type %s at %s"), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
	}

	return ResultPawn;
}

FString ADeathmatch::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if (ErrorMessage != "")
	{
		return ErrorMessage;
	}

	CharacterType Type = CharacterType(FCString::Atoi(*UGameplayStatics::ParseOption(Options, TEXT("CharacterType"))));
	TeamType Team = TeamType(FCString::Atoi(*UGameplayStatics::ParseOption(Options, TEXT("Team"))));

	//DebugPerpose
	if (Type == CharacterType::Lukriel)
	{
		Type = CharacterType::Allium;
	}
	if (Team == TeamType::Null)
	{
		Team = TeamType::Black;
	}

	if (ADefaultPlayerState* NewPlayerState = NewPlayerController->GetPlayerState<ADefaultPlayerState>())
	{
		NewPlayerState->SetCharacterBPRef(GetGameInstance<UDefaultGameInstance>()->GetCharacterBPRef(Type));
		//NewPlayerState->InitPlayerStats();
		NewPlayerState->SetTeam(Team);
	}

	return ErrorMessage;
}