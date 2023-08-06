// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Enemy.generated.h"

class AAIController;
class ATopDownCharacter;
UCLASS()
class TOPDOWN_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit(const FVector& ImpactPoint) override;

protected:
	virtual void BeginPlay() override;

	/**
	* AI Controll
	*/
	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY()
	ATopDownCharacter* PlayerCharacter;

private:

public:	
	AAIController* GetEnemyController() { return EnemyController; }
};
