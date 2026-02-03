// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSmallCoin.h"

// Sets default values
AItemSmallCoin::AItemSmallCoin()
{
    IntValue = 10;
    ItemType = FName("SmallCoin");
}

void AItemSmallCoin::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);
}
