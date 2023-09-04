// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GoldItem.h"
#include "Character/TopDownCharacter.h"
#include "Component/AttributeComponent.h"

void AGoldItem::Pickup(ATopDownCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("GoldPickupFuncCall"));
	GetGold(PlayerCharacter);
	ABaseItem::Pickup(PlayerCharacter);
}

void AGoldItem::GetGold(ATopDownCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		
	}
}
