// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TopDownCharacterController.h"
#include "HUD/GamePauseWidget.h"

void ATopDownCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATopDownCharacterController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ATopDownCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ATopDownCharacterController::GamePause);
}

void ATopDownCharacterController::GamePause()
{

}
