// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ItemHeal.generated.h"

UCLASS()
class U_260203_PROJECT008_API AItemHeal : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemHeal();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
