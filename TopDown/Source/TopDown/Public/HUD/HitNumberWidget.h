// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitNumberWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class TOPDOWN_API UHitNumberWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHitNumberText(int32 Damage);
	void PlayHitAnimation();
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HitNumberText;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HitNumberAnimation;
};
