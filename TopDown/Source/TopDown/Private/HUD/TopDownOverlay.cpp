// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TopDownOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTopDownOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UTopDownOverlay::SetEXPBarPercent(float Percent)
{
	if (EXPProgressBar)
	{
		EXPProgressBar->SetPercent(Percent);
	}
}

void UTopDownOverlay::SetMAXEXP(float MAXEXP)
{
	if (MAXEXPBlock)
	{
		const FString String = FString::Printf(TEXT("%f"), MAXEXP);
		const FText Text = FText::FromString(String);
		MAXEXPBlock->SetText(Text);
	}
}

void UTopDownOverlay::SetEXP(float EXP)
{
	if (EXPBlock)
	{
		const FString String = FString::Printf(TEXT("%f"), EXP);
		const FText Text = FText::FromString(String);
		EXPBlock->SetText(Text);
	}
}

void UTopDownOverlay::SetMaxHealt(float MaxHealth)
{
	if (MaxHealthBlock)
	{
		const FString String = FString::Printf(TEXT("%f"), MaxHealth);
		const FText Text = FText::FromString(String);
		MaxHealthBlock->SetText(Text);
	}
}

void UTopDownOverlay::SetHealth(float Health)
{
	if (HealthBlock)
	{
		const FString String = FString::Printf(TEXT("%f"), Health);
		const FText Text = FText::FromString(String);
		HealthBlock->SetText(Text);
	}
}
