// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "State/TopDownPlayerState.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
UCLASS()
class TOPDOWN_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	virtual void NativeConstruct() override;
	void SetGoldText();
private:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnUpgradeClicked();

	UFUNCTION()
	void OnExitClicked();


	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY()
	int32 Gold;

	UPROPERTY()
	FCharacterState CharacterState;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldTextBlock;
};
