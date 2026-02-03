// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCoin.h"
#include "ItemSmallCoin.generated.h"

UCLASS()
class U_260203_PROJECT008_API AItemSmallCoin : public AItemCoin
{
	GENERATED_BODY()
	
public:	
	AItemSmallCoin();

	virtual void ActivateItem(AActor* Activator) override;
};
