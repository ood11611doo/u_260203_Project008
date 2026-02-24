// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnArea.h"
#include "ItemCoin.h"
#include "../u_260203_Project008Character.h"
#include "GameInstanceBase.h"

ANewGameState::ANewGameState()
{
    Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	CurrentWave = 0;
	MaxLevels = 3;
	MaxWavePerLevel = 3;
}

void ANewGameState::BeginPlay()
{
    Super::BeginPlay();
}

void ANewGameState::StartGame()
{
	MaxLevels = LevelDatas.Num();
	SetState(EMatchState::Playing);
	StartLevel();
}
void ANewGameState::ResetData()
{
	CurrentLevelIndex = 0;
	CurrentWave = 0;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
			MyGameInstance->ResetGame();
		}
	}
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

	ResetElapsedTime();
    SpawnedCoinCount = 0;
    CollectedCoinCount = 0;

    TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnArea::StaticClass(), FoundVolumes);
	
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	LevelDatas[CurrentLevelIndex].WaveInfo[CurrentWave].ItemSpawnData->GetAllRows(ContextString, AllRows);

	LevelDuration = LevelDatas[CurrentLevelIndex].WaveInfo[CurrentWave].WaveTime;

	if (FoundVolumes.Num() > 0 && !AllRows.IsEmpty())
	{
		ASpawnArea* SpawnVol = Cast<ASpawnArea>(FoundVolumes[0]);
		for (const FItemSpawnRow* Row : AllRows)
		{
			for (int i = 0; i < Row->SpawnCount; i++)
			{
				AActor* SpawnedA = SpawnVol->SpawnItem(Row->ItemClass);
				if (SpawnedA)
				{
					SpawnedItems.Add(SpawnedA);
					if (SpawnedA->IsA(AItemCoin::StaticClass()))
					{
						SpawnedCoinCount++;
					}
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
	
	UE_LOG(LogTemp, Warning, TEXT("Level %d - Wave %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		CurrentWave + 1,
		SpawnedCoinCount);
}

void ANewGameState::OnLevelTimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Level %d - Wave %d Time Up!"), CurrentLevelIndex + 1, CurrentWave + 1);
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	OnGameOver();
}

void ANewGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Log, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);
	
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndCheck();
	}
}

void ANewGameState::EndCheck()
{
	for (AActor* Actor : SpawnedItems)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}

	if (CurrentWave < MaxWavePerLevel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Level %d - Wave %d Done!"), CurrentLevelIndex + 1, CurrentWave + 1));
		EndWave();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Level %d Done!"), CurrentLevelIndex + 1));
		EndLevel();
	}
}

void ANewGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentWave++;

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
			AddScore(Score);
			MyGameInstance->CurrentWave = CurrentWave;
		}
	}

	if (CurrentWave >= MaxWavePerLevel)
	{
		EndLevel();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(LevelTimerHandle);
		StartLevel();
	}
}

void ANewGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentWave = 0;
	CurrentLevelIndex++;

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UGameInstanceBase* MyGameInstance = Cast<UGameInstanceBase>(GameInstance))
		{
            AddScore(Score);
            MyGameInstance->CurrentLevelIndex = CurrentLevelIndex;
			MyGameInstance->CurrentWave = CurrentWave;
		}
	}

	if (LevelDatas.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelDatas[CurrentLevelIndex].LevelMapName);
	}
	else
	{
		OnGameOver();
	}
}


void ANewGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
	ACharacter* RawChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Au_260203_Project008Character* MyChar = Cast<Au_260203_Project008Character>(RawChar);

	for (AActor* Actor : SpawnedItems)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}

	if (MyChar)
	{
		MyChar->EndGame();
	}

	SetState(EMatchState::GameOver);
}

void ANewGameState::ResetElapsedTime()
{
	ElapsedTime = 0.0f;
}