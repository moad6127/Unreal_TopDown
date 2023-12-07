// Fill out your copyright notice in the Description page of Project Settings.


#include "State/TopDownPlayerState.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Kismet/GameplayStatics.h"

void ATopDownPlayerState::SaveCharacterState(FCharacterState SaveCharacterState)
{
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}

	TopDownSaveGame->CharacterState = SaveCharacterState;

	if (UGameplayStatics::SaveGameToSlot(TopDownSaveGame, SaveSlotName, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveData"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveDataFail!!!"));
	}
}

void ATopDownPlayerState::SaveGold(int32 SaveGold)
{
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}

	TopDownSaveGame->Gold = SaveGold;

	if (UGameplayStatics::SaveGameToSlot(TopDownSaveGame, SaveSlotName, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveData"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveDataFail!!!"));
	}
}

void ATopDownPlayerState::SavePlayerGold(int32 SaveGold)
{
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}

	TopDownSaveGame->Gold += SaveGold;

	if (UGameplayStatics::SaveGameToSlot(TopDownSaveGame, SaveSlotName, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveData"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveDataFail!!!"));
	}
}
