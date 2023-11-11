// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "State/TopDownPlayerState.h"
#include "LevelUpSubSlotWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class ULevelUpWidget;
class ATopDownCharacter;
UCLASS()
class TOPDOWN_API ULevelUpSubSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void LevelUpButtonClicked();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NowLevelText;

	UPROPERTY(meta = (BindWidget))
	UButton* LevelUpButton;

	ECharacterState LevelupState;

	UPROPERTY()
	ULevelUpWidget* ParentWidget;

	UPROPERTY()
	ATopDownCharacter* Character;

public:

	FORCEINLINE void SetState(ECharacterState State) { LevelupState = State; }
	FORCEINLINE void SetParentWidget(ULevelUpWidget* PWidget) { ParentWidget = PWidget; }
};
