// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"

/**
 * 
 */
class UTopDownOverlay;
UCLASS()
class TOPDOWN_API ATopDownHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, Category =TopDown)
	TSubclassOf<UTopDownOverlay> TopDownOverlayClass;

	UPROPERTY()
	UTopDownOverlay* TopDownOverlay;

public:
	FORCEINLINE UTopDownOverlay* GetTopDownOverlay() const { return TopDownOverlay; }
};

