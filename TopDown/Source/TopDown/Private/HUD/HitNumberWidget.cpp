// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HitNumberWidget.h"
#include "Components/TextBlock.h"

void UHitNumberWidget::SetHitNumberText(int32 Damage)
{
	if (HitNumberText)
	{
		const FString String = FString::Printf(TEXT("%d"), Damage);
		const FText Text = FText::FromString(String);
		HitNumberText->SetText(Text);
	}
}
