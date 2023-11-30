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

	auto TopDownSaveGame = Cast<UTopDownSaveGame>(
		UGameplayStatics::LoadGameFromSlot(PlayerCharacterState->GetSaveSlotName(), 0));
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
	InitUpgradeBoxButton();
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

void UUpgrade::InitUpgradeBoxButton()
{
	if (DamageLevelupButton)
	{
		DamageLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::DamageLevelupButtonClicked);
	}
	if (HealthLevelupButton)
	{
		HealthLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::HealthLevelupButtonClicked);
	}
	if (HealthRegenLevelupButton)
	{
		HealthRegenLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::HealthRegenLevelupButtonClicked);
	}
	if (ArmorLevelupButton)
	{
		ArmorLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::ArmorLevelupButtonClicked);
	}
	if (AttackSpeedLevelupButton)
	{
		AttackSpeedLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::AttackSpeedLevelupButtonClicked);
	}
	if (SpeedLevelupButton)
	{
		SpeedLevelupButton->OnClicked.AddDynamic(this, &UUpgrade::SpeedLevelupButtonClicked);
	}
}

void UUpgrade::SetWidgets()
{
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

void UUpgrade::DamageLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.DamageLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_DamageLevel);
		SetDamageBox();
		SetGoldText();
	}
}

void UUpgrade::SetHealthBox()
{
	int32 NeedCoins = CharacterState.HealthLevel * BaseUpgradeNeedCoins;
	SetTextBlock(HNLevel, CharacterState.HealthLevel);
	SetTextBlock(HNCoin, NeedCoins);
}

void UUpgrade::HealthLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.HealthLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_HealtLevel);
		SetHealthBox();
		SetGoldText();
	}
}


void UUpgrade::SetHealthRegenBox()
{
	int32 NeedCoins = CharacterState.HealthRegenLevel * BaseUpgradeNeedCoins;
	SetTextBlock(HRNLevel, CharacterState.HealthRegenLevel);
	SetTextBlock(HRNCoin, NeedCoins);
}

void UUpgrade::HealthRegenLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.HealthRegenLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_HealthRegenLevel);
		SetHealthRegenBox();
		SetGoldText();
	}
}

void UUpgrade::SetArmorBox()
{
	int32 NeedCoins = CharacterState.ArmorLevel * BaseUpgradeNeedCoins;
	SetTextBlock(ANLevel, CharacterState.ArmorLevel);
	SetTextBlock(ANCoin, NeedCoins);
}

void UUpgrade::ArmorLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.ArmorLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_ArmorLevel);
		SetArmorBox();
		SetGoldText();
	}
}

void UUpgrade::SetAttackSpeedBox()
{
	int32 NeedCoins = CharacterState.AttackSpeedLevel * BaseUpgradeNeedCoins;
	SetTextBlock(ASNLevel, CharacterState.AttackSpeedLevel);
	SetTextBlock(ASNCoin, NeedCoins);
}

void UUpgrade::AttackSpeedLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.AttackSpeedLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_AttackSpeedLevel);
		SetAttackSpeedBox();
		SetGoldText();
	}
}

void UUpgrade::SetSpeedBox()
{
	int32 NeedCoins = CharacterState.SpeedLevel * BaseUpgradeNeedCoins;
	SetTextBlock(SNLevel, CharacterState.SpeedLevel);
	SetTextBlock(SNCoin, NeedCoins);
}

void UUpgrade::SpeedLevelupButtonClicked()
{
	int32 NeedCoins = CharacterState.SpeedLevel * BaseUpgradeNeedCoins;
	if (NeedCoins <= Gold)
	{
		Gold = FMath::Clamp(Gold - NeedCoins, 0, 999999);
		CharacterState.LevelUp(ECharacterState::ECS_SpeedLevel);
		SetSpeedBox();
		SetGoldText();
	}
}

void UUpgrade::SetGoldText()
{
	SetTextBlock(GoldTextBlock, Gold);
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


