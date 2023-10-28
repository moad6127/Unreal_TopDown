// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "State/TopDownPlayerState.h"
#include "Upgrade.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class TOPDOWN_API UUpgrade : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnSaveButtonClicked();

	UFUNCTION()
	void OnCancleButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	//DamageBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DMNLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DMNCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* DamageLevelupButton;

	//HealthBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HNLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HNCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* HealthLevelupButton;
	
	//HealthRegenBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HRNLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HRNCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* HealthRegenLevelupButton;

	//ArmorBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ANLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ANCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* ArmorLevelupButton;

	//AttackSpeedBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ASNLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ASNCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* AttackSpeedLevelupButton;

	//SpeedBox
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SNLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SNCoin;

	UPROPERTY(meta = (BindWidget))
	UButton* SpeedLevelupButton;

	FCharacterState CharacterState;

	UPROPERTY()
	ATopDownPlayerState* PlayerCharacterState;
};
