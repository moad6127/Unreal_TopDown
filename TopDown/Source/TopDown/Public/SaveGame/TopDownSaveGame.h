// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "State/TopDownPlayerState.h"
#include "TopDownSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UTopDownSaveGame();

	UPROPERTY()
	int32 Gold;

	UPROPERTY()
	FCharacterState CharacterState;

	FString PlayerName;
};
