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

};

UCLASS()
class TOPDOWN_API ATopDownPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FCharacterState CharacterState;

public:

	FORCEINLINE FCharacterState GetCharacterState() { return CharacterState; }
};
