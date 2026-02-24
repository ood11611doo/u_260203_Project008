// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/GameState.h"
#include "NewGameState.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	WaitingToStart,
	Playing,
	GameOver
};

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float WaveTime;
	UPROPERTY(EditAnywhere)
	UDataTable* ItemSpawnData;
};

USTRUCT(BlueprintType)
struct FStageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName LevelMapName;
	UPROPERTY(EditAnywhere)
	TArray<FWaveInfo> WaveInfo;
};

UCLASS()
class U_260203_PROJECT008_API ANewGameState : public AGameState
{
	GENERATED_BODY()
	
public:
    ANewGameState();

	virtual void BeginPlay() override;

	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResetData();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EMatchState CurrentState = EMatchState::WaitingToStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentWave;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxWavePerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FStageInfo> LevelDatas;
	
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const;
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "Game Statistics")
	void ResetElapsedTime();

	void SetState(EMatchState NewState) { CurrentState = NewState; }
	void StartLevel();
	void OnLevelTimeUp();
	void OnCoinCollected();
	void EndCheck();
	void EndWave();
	void EndLevel();

protected:
	UPROPERTY()
	TArray<AActor*> SpawnedItems;
};
