// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "GoldItem.generated.h"

/**
 * 
 */
class ATopDownCharacter;


UCLASS()
class TOPDOWN_API AGoldItem : public ABaseItem
{
	GENERATED_BODY()
public:
	virtual void Pickup(ATopDownCharacter* PlayerCharacter) override;

private:

	void GetGold(ATopDownCharacter* PlayerCharacter);

	UPROPERTY(EditAnywhere)
	int32 Gold;
};
