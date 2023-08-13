// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemyAnimInstance.h"
#include "Enemy/Enemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Enemy = Cast<AEnemy>(TryGetPawnOwner());

}

void UBaseEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Enemy == nullptr)
	{
		Enemy = Cast<AEnemy>(TryGetPawnOwner());
	}

	if (Enemy == nullptr)
	{
		return;
	}

	FVector Velocity = Enemy->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	EnemyDeathPose = Enemy->GetDeathPose();

}
