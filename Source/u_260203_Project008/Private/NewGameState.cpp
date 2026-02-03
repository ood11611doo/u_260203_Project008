// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnArea.h"
#include "ItemCoin.h"
#include "GameInstanceBase.h"

ANewGameState::ANewGameState()
{
    Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void ANewGameState::BeginPlay()
{
    Super::BeginPlay();
    StartLevel();
}

int32 ANewGameState::GetScore() const
{
    return Score;
}

void ANewGameState::AddScore(int32 Points)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
			MyGameInstance->AddToScore(Points);
		}
	}
}

void ANewGameState::StartLevel()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
            CurrentLevelIndex = MyGameInstance->CurrentLevelIndex;
		}
	}

    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;

    TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnArea::StaticClass(), FoundVolumes);
	
	const int32 ItemToSpawn = 40;
	
	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnArea* SpawnVolume = Cast<ASpawnArea>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(AItemCoin::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}				
		}
	}

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ANewGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);
	
	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void ANewGameState::OnLevelTimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Level %d Time Up!"), CurrentLevelIndex + 1);
	EndLevel();
}

void ANewGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Log, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);
	
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}

void ANewGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentLevelIndex++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
            AddScore(Score);
            MyGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}


void ANewGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
}