// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EXPItem.h"
#include "Character/TopDownCharacter.h"
#include "Component/AttributeComponent.h"

void AEXPItem::Pickup(ATopDownCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("EXPPickupFuncCall"));
	EXPUp(PlayerCharacter);
	ABaseItem::Pickup(PlayerCharacter);
}

void AEXPItem::EXPUp(ATopDownCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetEXPPoint(EXP);
	}
}
