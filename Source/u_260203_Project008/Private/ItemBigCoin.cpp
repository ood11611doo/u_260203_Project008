// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBigCoin.h"

// Sets default values
AItemBigCoin::AItemBigCoin()
{
    IntValue = 50;
    ItemType = FName("BigCoin");
}

void AItemBigCoin::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);
}