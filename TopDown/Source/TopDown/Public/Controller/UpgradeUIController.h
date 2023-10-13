// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UpgradeUIController.generated.h"

/**
 * 
 */
class UUpgrade;
UCLASS()
class TOPDOWN_API AUpgradeUIController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUpgrade> UpgradeWidgetClass;

	UPROPERTY()
	UUpgrade* UpgradeWidgetInstance;
};
