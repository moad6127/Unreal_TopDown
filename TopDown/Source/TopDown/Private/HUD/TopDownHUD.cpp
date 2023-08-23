// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TopDownHUD.h"
#include "HUD/TopDownOverlay.h"

void ATopDownHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && TopDownOverlayClass)
		{
			TopDownOverlay = CreateWidget<UTopDownOverlay>(Controller, TopDownOverlayClass);
			TopDownOverlay->AddToViewport();
		}
	}

}
