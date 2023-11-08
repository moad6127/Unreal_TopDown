// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TopDownPlayerState.generated.h"

/**
 * 
 */
UENUM()
enum class ECharacterState : uint8
{
	ECS_DamageLevel UMETA(DisplayName = DamageLevel),
	ECS_HealtLevel UMETA(DisplayName = HealtLevel),
	ECS_HealthRegenLevel UMETA(DisplayName = HealthRegenLevel),
	ECS_ArmorLevel UMETA(DisplayName = ArmorLevel),
	ECS_AttackSpeedLevel UMETA(DisplayName = AttackSpeedLevel),
	ECS_SpeedLevel UMETA(DisplayName = SpeedLevel),

	ECS_DefaultMax UMETA(DisplaySnme = DefaultMax)
};


USTRUCT()
struct FCharacterState
{
	GENERATED_USTRUCT_BODY()
public:

	FCharacterState() :
		DamageLevel(1),
		HealthLevel(1),
		HealthRegenLevel(1),
		ArmorLevel(1),
		AttackSpeedLevel(1),
		SpeedLevel(1)
	{};

	UPROPERTY(EditAnywhere)
	int32 DamageLevel;

	UPROPERTY(EditAnywhere)
	int32 HealthLevel;

	UPROPERTY(EditAnywhere)
	int32 HealthRegenLevel;

	UPROPERTY(EditAnywhere)
	int32 ArmorLevel;

	UPROPERTY(EditAnywhere)
	int32 AttackSpeedLevel;

	UPROPERTY(EditAnywhere)
	int32 SpeedLevel;

	void LevelUp()
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelUp"));

		DamageLevel++;
		HealthLevel++;
		HealthRegenLevel++;
		ArmorLevel++;
		AttackSpeedLevel++;
		SpeedLevel++;
	}
	void LevelUp(ECharacterState Oper)
	{
		switch (Oper)
		{
		case ECharacterState::ECS_DamageLevel:
			UE_LOG(LogTemp, Warning, TEXT("DamageLevelUp"));
			DamageLevel++;
			break;
		case ECharacterState::ECS_HealtLevel:
			UE_LOG(LogTemp, Warning, TEXT("HealthLevelUp"));
			HealthLevel++;
			break;
		case ECharacterState::ECS_HealthRegenLevel:
			UE_LOG(LogTemp, Warning, TEXT("HealthRegenLevelUp"));
			HealthRegenLevel++;
			break;
		case ECharacterState::ECS_ArmorLevel:
			UE_LOG(LogTemp, Warning, TEXT("ArmorLevelUp"));
			ArmorLevel++;
			break;
		case ECharacterState::ECS_AttackSpeedLevel:
			UE_LOG(LogTemp, Warning, TEXT("AttackSpeedLevelUp"));
			AttackSpeedLevel++;
			break;
		case ECharacterState::ECS_SpeedLevel:
			UE_LOG(LogTemp, Warning, TEXT("SpeedLevelUp"));
			SpeedLevel++;
			break;
		default:
			break;
		}
	}

	int32 ReturnStateLevel(ECharacterState Oper)
	{
		switch (Oper)
		{
		case ECharacterState::ECS_DamageLevel:
			return DamageLevel;
			break;
		case ECharacterState::ECS_HealtLevel:
			return HealthLevel;
			break;
		case ECharacterState::ECS_HealthRegenLevel:
			return HealthRegenLevel;
			break;
		case ECharacterState::ECS_ArmorLevel:
			return ArmorLevel;
			break;
		case ECharacterState::ECS_AttackSpeedLevel:
			return AttackSpeedLevel;
			break;
		case ECharacterState::ECS_SpeedLevel:
			return SpeedLevel;
			break;
		case ECharacterState::ECS_DefaultMax:
			break;
		}
	}

	FText ReturnStateName(ECharacterState Oper)
	{
		FString TextStrnig;
		FText Text; 
		switch (Oper)
		{
		case ECharacterState::ECS_DamageLevel:
			TextStrnig = FString(TEXT("Damage"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_HealtLevel:
			TextStrnig = FString(TEXT("Health"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_HealthRegenLevel:
			TextStrnig = FString(TEXT("HealthRegen"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_ArmorLevel:
			TextStrnig = FString(TEXT("Armor"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_AttackSpeedLevel:
			TextStrnig = FString(TEXT("AttackSpped"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_SpeedLevel:
			TextStrnig = FString(TEXT("Speed"));
			Text = FText::FromString(TextStrnig);
			return Text;
			break;
		case ECharacterState::ECS_DefaultMax:
			break;
		}
	}
};

UCLASS()
class TOPDOWN_API ATopDownPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FCharacterState CharacterState;

	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName = TEXT("Player");

public:

	FORCEINLINE FCharacterState GetCharacterState() { return CharacterState; }
	FORCEINLINE FString GetSaveSlotName() const { return SaveSlotName; }
	void SaveCharacterState(FCharacterState SaveCharacterState);
};
