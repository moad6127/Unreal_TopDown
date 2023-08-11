// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHealthBarComponent.generated.h"

/**
 * 
 */
class UHealthBar;
UCLASS()
class TOPDOWN_API UEnemyHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	void SetHealthPercent(float Percent);

private:
	UPROPERTY()
	UHealthBar* HealthBarWidget;
};
