// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ATopDownCharacter;
class TOPDOWN_API IPickupInterface
{
	GENERATED_BODY()

public:

	virtual void Pickup(ATopDownCharacter* PlayerCharacter);
};
