// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/TopDownPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "TopDownCharacterController.generated.h"

/**
 * 
 */

class UGamePauseWidget;
class UGameResultMenu;
class ULevelUpWidget;

UCLASS()
class TOPDOWN_API ATopDownCharacterController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	void ShowResultWidget();
	void GamePause();
	void LevelUp();
protected:
	virtual void SetupInputComponent() override;
private:


	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<class UUserWidget> GamePauseWidgetClass;

	UPROPERTY()
	UGamePauseWidget* GamePauseWidget;

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<UUserWidget> GameResultWidgetClass;

	UPROPERTY()
	UGameResultMenu* GameResultWidget;

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<ULevelUpWidget> LevelUpWidgetClass;

	UPROPERTY()
	ULevelUpWidget* LevelUpWidget;


	TArray<ECharacterState> ChooseRandomState();
};
