// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "EXPItem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API AEXPItem : public ABaseItem
{
	GENERATED_BODY()
	

private:

	UPROPERTY(EditAnywhere)
	float EXP;
public:

};
