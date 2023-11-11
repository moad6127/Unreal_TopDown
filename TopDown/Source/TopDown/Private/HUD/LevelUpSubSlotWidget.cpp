// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LevelUpSubSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/TopDownCharacter.h"
#include "HUD/LevelUpWidget.h"

void ULevelUpSubSlotWidget::NativeConstruct()
{
	FCharacterState State;
	FText Text = State.ReturnStateName(LevelupState);
	if (NameText)
	{
		NameText->SetText(Text);
	}
	FString String = FString::Printf(TEXT("%d"), State.ReturnStateLevel(LevelupState));
	Text = FText::FromString(String);
	if (NowLevelText)
	{
		NowLevelText->SetText(Text);
	}
	if (LevelUpButton)
	{
		LevelUpButton->OnClicked.AddDynamic(this, &ULevelUpSubSlotWidget::LevelUpButtonClicked);
	}
}

void ULevelUpSubSlotWidget::LevelUpButtonClicked()
{
	ATopDownCharacter* Character = Cast<ATopDownCharacter>(GetOwningPlayerPawn());
	Character->StateLevelUp(LevelupState);
	ParentWidget->RemoveFromParent();
}
