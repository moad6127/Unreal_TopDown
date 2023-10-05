// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameResultMenu.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class TOPDOWN_API UGameResultMenu : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void TitleButtonClicked();

	void SetGoldText();

private:

	UPROPERTY(meta = (BindWidget))
	UButton* TitleButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;
};
