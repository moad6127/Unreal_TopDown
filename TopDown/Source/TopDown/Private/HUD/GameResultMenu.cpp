// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameResultMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Character/TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"

void UGameResultMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (TitleButton)
	{
		TitleButton->OnClicked.AddDynamic(this, &UGameResultMenu::TitleButtonClicked);
	}
	SetGoldText();
}

void UGameResultMenu::TitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TitleMap"));
}

void UGameResultMenu::SetGoldText()
{
	ATopDownCharacter* Character = Cast<ATopDownCharacter>(GetOwningPlayerPawn());
	if (GoldText && Character)
	{
		const FString String = FString::Printf(TEXT("%d"),Character->GetPlayerGold());
		const FText Text = FText::FromString(String);
		GoldText->SetText(Text);
		Character->SaveGame();
	}
}
