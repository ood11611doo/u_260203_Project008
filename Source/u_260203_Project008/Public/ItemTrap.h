// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "ItemTrap.generated.h"

UCLASS()
class U_260203_PROJECT008_API AItemTrap : public AItemBase
{
	GENERATED_BODY()
	
public:	
	AItemTrap();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ActiveCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float ActiveDelay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float ActiveRadius;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	int ActiveDamage;

	FTimerHandle ActiveTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
};
