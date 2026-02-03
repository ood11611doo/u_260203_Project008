// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnArea.generated.h"

class UBoxComponent;

UCLASS()
class U_260203_PROJECT008_API ASpawnArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnArea();
	
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnRandomItem();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
    USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
    UBoxComponent* SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

	UFUNCTION(BlueprintCallable, Category="Spawning")
    FVector GetRandomPointInVolume() const;
    FItemSpawnRow* GetRandomItem() const;
    UFUNCTION(BlueprintCallable, Category="Spawning")
    AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
};
