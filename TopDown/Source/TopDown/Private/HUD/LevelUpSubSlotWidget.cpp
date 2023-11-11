// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LevelUpSubSlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/TopDownCharacter.h"
#include "Controller/TopDownCharacterController.h"
#include "HUD/LevelUpWidget.h"

void ULevelUpSubSlotWidget::NativeConstruct()
{
	Character = Character == nullptr ? Cast<ATopDownCharacter>(GetOwningPlayerPawn()) : Character;
	FCharacterState State;
	if (Character)
	{
		State = Character->GetCharacterState();
	}

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
	Character = Character == nullptr ? Cast<ATopDownCharacter>(GetOwningPlayerPawn()) : Character;
	ATopDownCharacterController* Controller = Cast<ATopDownCharacterController>(GetOwningPlayer());

	if (Controller && Character && ParentWidget)
	{
		Character->StateLevelUp(LevelupState);
		ParentWidget->RemoveFromParent();
		Controller->SetPause(false);
		Character->SetPlayerData();
	}

}
