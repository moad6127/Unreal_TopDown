// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
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
}

void UTitleWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("TopDownMap"));
}

void UTitleWidget::OnUpgradeClicked()
{
}

void UTitleWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}
