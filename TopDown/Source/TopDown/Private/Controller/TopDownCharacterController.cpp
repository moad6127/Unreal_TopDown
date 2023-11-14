// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TopDownCharacterController.h"
#include "HUD/LevelUpWidget.h"
#include "HUD/GamePauseWidget.h"
#include "HUD/GameResultMenu.h"

void ATopDownCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATopDownCharacterController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ATopDownCharacterController::ShowResultWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("GameReuslt!!"));

	if (GameResultWidgetClass)
	{
		GameResultWidget = CreateWidget<UGameResultMenu>(this, GameResultWidgetClass);
		if (GameResultWidget)
		{
			GameResultWidget->AddToViewport(3);
			SetPause(true);
		}
	}
}

void ATopDownCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

//	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ATopDownCharacterController::GamePause);
}

TArray<ECharacterState> ATopDownCharacterController::ChooseRandomState()
{
	TArray<ECharacterState> Result;
	while (Result.Num() < 3)
	{
		int32 RandomValue = FMath::RandRange(0, static_cast<int32>(ECharacterState::ECS_DefaultMax) - 1);
		ECharacterState RandEnumMember = static_cast<ECharacterState>(RandomValue);

		if (!Result.Contains(RandEnumMember))
		{
			Result.Add(RandEnumMember);
		}
	}
	return Result;
}

void ATopDownCharacterController::GamePause()
{
	UE_LOG(LogTemp, Warning, TEXT("GamePause!!"));
	if (GamePauseWidgetClass)
	{
		GamePauseWidget = CreateWidget<UGamePauseWidget>(this, GamePauseWidgetClass);
	}
	if (GamePauseWidget)
	{
		GamePauseWidget->AddToViewport(3);
		SetPause(true);
	}
}

void ATopDownCharacterController::LevelUp()
{
	UE_LOG(LogTemp, Warning, TEXT("LevelUp!!"));
	if (LevelUpWidgetClass)
	{
		LevelUpWidget = CreateWidget<ULevelUpWidget>(this, LevelUpWidgetClass);
		if (LevelUpWidget)
		{
			LevelUpWidget->SetPanel(ChooseRandomState());
			LevelUpWidget->AddToViewport(3);
			SetPause(true);
		}
	}
}
