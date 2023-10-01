// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownCharacterController.generated.h"

/**
 * 
 */

class UGamePauseWidget;
UCLASS()
class TOPDOWN_API ATopDownCharacterController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
protected:

	virtual void SetupInputComponent() override;


private:
	void GamePause();

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<class UUserWidget> GamePauseWidgetClass;
	UGamePauseWidget* GamePauseWidget;
};
