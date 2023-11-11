// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LevelUpWidget.h"
#include "Components/WrapBox.h"
#include "HUD/LevelUpSubSlotWidget.h"


void ULevelUpWidget::SetPanel(TArray<ECharacterState> LevelupState)
{
	if (LevelupSubSlot)
	{
		LevelUpPanel->ClearChildren();
		for (auto e : LevelupState)
		{
			ULevelUpSubSlotWidget* SubSlot = CreateWidget<ULevelUpSubSlotWidget>(this, LevelupSubSlot);

			SubSlot->SetState(e);
			SubSlot->SetParentWidget(this);
			LevelUpPanel->AddChildToWrapBox(SubSlot);
			
		}
	}

}


