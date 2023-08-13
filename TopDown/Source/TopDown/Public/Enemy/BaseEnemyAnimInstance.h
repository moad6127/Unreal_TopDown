// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterType.h"
#include "BaseEnemyAnimInstance.generated.h"

/**
 * 
 */

class AEnemy;

UCLASS()
class TOPDOWN_API UBaseEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	

private:
	UPROPERTY(BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	AEnemy* Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	EDeathPose EnemyDeathPose;

};
