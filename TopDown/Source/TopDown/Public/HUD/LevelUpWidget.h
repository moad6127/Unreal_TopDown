// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/TopDownPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */
class UWrapBox;
class ULevelUpSubSlotWidget;

UCLASS()
class TOPDOWN_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UWrapBox* LevelUpPanel;

	TArray<ECharacterState> CharacterState;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULevelUpSubSlotWidget> LevelupSubSlot;

	virtual void NativeConstruct() override;

	void SetPanel();

public:
	FORCEINLINE void SetCharacterState(TArray<ECharacterState> State) { CharacterState = State; }
};
