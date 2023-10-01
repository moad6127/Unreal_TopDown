// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GamePauseWidget.h"
#include "Components/Button.h"


void UGamePauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UGamePauseWidget::ReturnButtonClicked);
	}
	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UGamePauseWidget::TitleButtonClicked);
	}
}

void UGamePauseWidget::ReturnButtonClicked()
{

}

void UGamePauseWidget::TitleButtonClicked()
{
}
