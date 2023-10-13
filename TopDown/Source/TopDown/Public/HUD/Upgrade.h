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

	FCharacterState CharacterState;

	UPROPERTY()
	ATopDownPlayerState* PlayerCharacterState;
};
