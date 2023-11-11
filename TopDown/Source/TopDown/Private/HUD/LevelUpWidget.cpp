// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LevelUpWidget.h"
#include "Components/WrapBox.h"
#include "HUD/LevelUpSubSlotWidget.h"
void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetPanel();
}

void ULevelUpWidget::SetPanel()
{
	if (LevelupSubSlot)
	{
		LevelUpPanel->ClearChildren();
		for (auto e : CharacterState)
		{
			ULevelUpSubSlotWidget* SubSlot = CreateWidget<ULevelUpSubSlotWidget>(this, LevelupSubSlot);

			LevelUpPanel->AddChildToWrapBox(SubSlot);
		}
	}

}
