// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHeal.h"
#include "u_260203_Project008/u_260203_Project008Character.h"

// Sets default values
AItemHeal::AItemHeal()
{
    HealAmount = 25.0f;
    ItemType = FName("Heal");
}

void AItemHeal::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d HP!"), HealAmount));
        if (Au_260203_Project008Character* Character = Cast<Au_260203_Project008Character>(Activator))
        {
            Character->AddHealth(static_cast<float>(HealAmount));
        }
        DestroyItem();
    }
}
