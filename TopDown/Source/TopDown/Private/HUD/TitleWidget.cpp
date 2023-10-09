// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Component/AttributeComponent.h"
#include "Components/TextBlock.h"

bool UTitleWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnStartClicked);
	}
	if (UpgradeButton)
	{
		UpgradeButton->OnClicked.AddDynamic(this, &UTitleWidget::OnUpgradeClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitClicked);
	}
	return true;
}

void UTitleWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto Attributes = GetDefault<UAttributeComponent>();
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(Attributes->GetSaveSlotName(), 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}
	Gold = TopDownSaveGame->Gold;
	CharacterState = TopDownSaveGame->CharacterState;
	SetGoldText();
}

void UTitleWidget::SetGoldText()
{
	if (GoldTextBlock)
	{
		const FString String = FString::Printf(TEXT("%d"), Gold);
		const FText Text = FText::FromString(String);
		GoldTextBlock->SetText(Text);
	}
}

void UTitleWidget::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("TopDownMap"));
}

void UTitleWidget::OnUpgradeClicked()
{
	CharacterState.LevelUp();
}

void UTitleWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}
