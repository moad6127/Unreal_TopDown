// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class TOPDOWN_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:


	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	
};
