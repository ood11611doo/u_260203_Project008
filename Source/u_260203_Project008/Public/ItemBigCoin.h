// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCoin.h"
#include "ItemBigCoin.generated.h"

UCLASS()
class U_260203_PROJECT008_API AItemBigCoin : public AItemCoin
{
	GENERATED_BODY()
	
public:	
	AItemBigCoin();

	virtual void ActivateItem(AActor* Activator) override;
};
