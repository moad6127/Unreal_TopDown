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
	int32 NeedCoins = CharacterState.DamageLevel * BaseUpgradeNeedCoins;
	SetTextBlock(DMNLevel, CharacterState.DamageLevel);
	SetTextBlock(DMNCoin, NeedCoins);
}

void UUpgrade::SetHealthBox()
{
	int32 NeedCoins = CharacterState.HealthLevel * BaseUpgradeNeedCoins;
	SetTextBlock(HNLevel, CharacterState.HealthLevel);
	SetTextBlock(HNCoin, NeedCoins);
}

void UUpgrade::SetHealthRegenBox()
{
	int32 NeedCoins = CharacterState.HealthRegenLevel * BaseUpgradeNeedCoins;
	SetTextBlock(HRNLevel, CharacterState.HealthRegenLevel);
	SetTextBlock(HRNCoin, NeedCoins);
}

void UUpgrade::SetArmorBox()
{
	int32 NeedCoins = CharacterState.ArmorLevel * BaseUpgradeNeedCoins;
	SetTextBlock(ANLevel, CharacterState.ArmorLevel);
	SetTextBlock(ANCoin, NeedCoins);
}

void UUpgrade::SetAttackSpeedBox()
{
	int32 NeedCoins = CharacterState.AttackSpeedLevel * BaseUpgradeNeedCoins;
	SetTextBlock(ASNLevel, CharacterState.AttackSpeedLevel);
	SetTextBlock(ASNCoin, NeedCoins);
}

void UUpgrade::SetSpeedBox()
{
	int32 NeedCoins = CharacterState.SpeedLevel * BaseUpgradeNeedCoins;
	SetTextBlock(SNLevel, CharacterState.SpeedLevel);
	SetTextBlock(SNCoin, NeedCoins);
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


