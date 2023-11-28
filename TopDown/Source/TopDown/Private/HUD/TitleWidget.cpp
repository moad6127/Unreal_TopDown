// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Component/AttributeComponent.h"
#include "Components/TextBlock.h"

bool UTitleWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
	}
	if (UpgradeButton)
	{
		UpgradeButton->OnClicked.AddDynamic(this, &UTitleWidget::OnUpgradeClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
	}
	return true;
}

void UTitleWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("TopDownMap"));
}

void UTitleWidget::OnUpgradeClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("UpgradeMap"));
}

void UTitleWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}
