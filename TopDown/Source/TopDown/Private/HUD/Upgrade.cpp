// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Upgrade.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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
	Gold = TopDownSaveGame->Gold;
	if (SaveButton)
	{
		SaveButton->OnClicked.AddDynamic(this, &UUpgrade::OnSaveButtonClicked);
	}
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UUpgrade::OnCancleButtonClicked);
	}
	SetWidgets();
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

void UUpgrade::SetWidgets()
{
	InitUpgradeBoxButton();
	SetDamageBox();
	SetHealthBox();
	SetHealthRegenBox();
	SetArmorBox();
	SetAttackSpeedBox();
	SetSpeedBox();
	SetGoldText();
}

void UUpgrade::SetDamageBox()
{
}

void UUpgrade::SetHealthBox()
{
}

void UUpgrade::SetHealthRegenBox()
{
}

void UUpgrade::SetArmorBox()
{
}

void UUpgrade::SetAttackSpeedBox()
{
}

void UUpgrade::SetSpeedBox()
{
}

void UUpgrade::SetGoldText()
{
	SetTextBlock(GoldTextBlock, Gold);
}

void UUpgrade::InitUpgradeBoxButton()
{

}

void UUpgrade::SetTextBlock(UTextBlock* TextBlock, int nums)
{
	if (TextBlock)
	{
		const FString String = FString::Printf(TEXT("%d"), nums);
		const FText Text = FText::FromString(String);
		TextBlock->SetText(Text);
	}
}


