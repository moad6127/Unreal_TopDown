// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/UpgradeUIController.h"
#include "Blueprint/UserWidget.h"
#include "HUD/Upgrade.h"
void AUpgradeUIController::BeginPlay()
{
	Super::BeginPlay();

	if (UpgradeWidgetClass)
	{
		UpgradeWidgetInstance = CreateWidget<UUpgrade>(this, UpgradeWidgetClass);
		if (UpgradeWidgetInstance)
		{
			UpgradeWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
		}
	}
}
