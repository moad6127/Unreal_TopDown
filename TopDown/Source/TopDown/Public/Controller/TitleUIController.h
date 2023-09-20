// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleUIController.generated.h"

/**
 * 
 */

class UUserWidget;
class UTitleWidget;

UCLASS()
class TOPDOWN_API ATitleUIController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTitleWidget> UIWidgetClass;

	UPROPERTY()
	UTitleWidget* UIWidgetInstance;
	
};
