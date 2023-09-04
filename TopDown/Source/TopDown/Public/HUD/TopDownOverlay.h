// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownOverlay.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;
UCLASS()
class TOPDOWN_API UTopDownOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthBarPercent(float Percent);
	void SetEXPBarPercent(float Percent);
	void SetMAXEXP(float MAXEXP);
	void SetEXP(float EXP);
	void SetMaxHealt(float MaxHealth);
	void SetHealth(float Health);
	void SetLevel(int32 PlayerLevel);
	void SetMatchCountDown(float CountDownTime);
private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MAXEXPBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EXPBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealthBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterLevelBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchCountDownText;
};
