// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "ItemCoin.generated.h"

UCLASS()
class U_260203_PROJECT008_API AItemCoin : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemCoin();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 IntValue;

	virtual void ActivateItem(AActor* Activator) override;
};
