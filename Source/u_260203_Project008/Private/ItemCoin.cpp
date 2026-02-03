// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCoin.h"
#include "Engine/World.h"
#include "NewGameState.h"

// Sets default values
AItemCoin::AItemCoin()
{
    IntValue = 0;
    ItemType = FName("BaseCoin");
}

void AItemCoin::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d points!"), IntValue));
        if (UWorld* World = GetWorld())
        {
            if (ANewGameState* GameState = World->GetGameState<ANewGameState>())
            {
                GameState->AddScore(IntValue);
                GameState->OnCoinCollected();
            }
        }
        DestroyItem();
    }
}

