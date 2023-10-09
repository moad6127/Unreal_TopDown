// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TopDownPlayerState.generated.h"

/**
 * 
 */
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
