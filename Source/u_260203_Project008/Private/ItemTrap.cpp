// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTrap.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemTrap::AItemTrap()
{
    ActiveDelay = 4.0f;
    ActiveRadius = 300.0f;
    ActiveDamage = 30;
    ItemType = FName("Trap");

    ActiveCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ActiveCollision"));
    ActiveCollision->InitSphereRadius(ActiveRadius);
    ActiveCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    ActiveCollision->SetupAttachment(Scene);
}

void AItemTrap::ActivateItem(AActor* Activator)
{
    GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, this, &AItemTrap::Explode, ActiveDelay);
}

void AItemTrap::Explode()
{
    TArray<AActor*> OverlappingActors;
    ActiveCollision->GetOverlappingActors(OverlappingActors);
    for (AActor* Actor : OverlappingActors)
    {
        if (Actor && Actor->ActorHasTag("Player"))
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Player damaged %d by MineItem"), ActiveDamage));
            UGameplayStatics::ApplyDamage(
	              Actor,
	              ActiveDamage,
	              nullptr,
	              this,
	              UDamageType::StaticClass()
	          );
        }
    }
    DestroyItem();
}
