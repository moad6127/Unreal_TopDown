// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TitleUIController.h"
#include "Blueprint/UserWidget.h"
#include "HUD/TitleWidget.h"

void ATitleUIController::BeginPlay()
{
	Super::BeginPlay();

	if (UIWidgetClass)
	{
		UIWidgetInstance = CreateWidget<UTitleWidget>(this, UIWidgetClass);
		if (UIWidgetInstance)
		{
			UIWidgetInstance->AddToViewport();

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->TakeWidget());
			Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(Mode);
			bShowMouseCursor = true;
		}
	}
}
