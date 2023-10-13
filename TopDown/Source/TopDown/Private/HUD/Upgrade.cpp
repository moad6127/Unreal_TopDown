// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Upgrade.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UUpgrade::NativeConstruct()
{
	PlayerCharacterState = Cast<ATopDownPlayerState>(GetOwningPlayerState());
	if (PlayerCharacterState == nullptr)
	{
		return;
	}

	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(PlayerCharacterState->GetSaveSlotName(), 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}
	CharacterState = TopDownSaveGame->CharacterState;

	if (SaveButton)
	{
		SaveButton->OnClicked.AddDynamic(this, &UUpgrade::OnSaveButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UUpgrade::OnCancleButtonClicked);
	}
}

void UUpgrade::OnSaveButtonClicked()
{
	if (PlayerCharacterState)
	{
		PlayerCharacterState->SaveCharacterState(CharacterState);
		UGameplayStatics::OpenLevel(this, TEXT("TitleMap"));
	}
}

void UUpgrade::OnCancleButtonClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("TitleMap"));
}
