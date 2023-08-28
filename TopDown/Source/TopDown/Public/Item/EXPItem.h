// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "EXPItem.generated.h"

/**
 * 
 */
class ATopDownCharacter;

UCLASS()
class TOPDOWN_API AEXPItem : public ABaseItem
{
	GENERATED_BODY()
public:
	virtual void Pickup(ATopDownCharacter* PlayerCharacter) override;
	
private:

	void EXPUp(ATopDownCharacter* PlayerCharacter);

	UPROPERTY(EditAnywhere)
	float EXP;

	
public:
	FORCEINLINE void SetEXP(float EXPPoint) { EXP = EXPPoint; }
};
