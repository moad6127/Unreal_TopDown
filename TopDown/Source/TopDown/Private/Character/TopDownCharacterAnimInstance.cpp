// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TopDownCharacterAnimInstance.h"
#include "Character/TopDownCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTopDownCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	TopDownCharacter = Cast<ATopDownCharacter>(TryGetPawnOwner());
}

void UTopDownCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (TopDownCharacter == nullptr)
	{
		TopDownCharacter = Cast<ATopDownCharacter>(TryGetPawnOwner());
	}

	if (TopDownCharacter == nullptr)
	{
		return;
	}

	FVector Velocity = TopDownCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = TopDownCharacter->GetCharacterMovement()->IsFalling();

	bIsAcceleratiog = TopDownCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() >0.f ? true : false;
}
