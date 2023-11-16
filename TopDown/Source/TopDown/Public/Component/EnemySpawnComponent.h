// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawnComponent.generated.h"

class ATopDownCharacter;
class AEnemy;
class UEnvQuery;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemySpawnComponent();
	friend ATopDownCharacter;

	void CheckTime(int32 Time);
	void SpawnEnemy();

protected:
	virtual void BeginPlay() override;



private:
	UPROPERTY()
	ATopDownCharacter* Character;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AEnemy>> EnemyClasses;

	UPROPERTY()
	AEnemy* SpawnedEnemy;

	int32 SpawnTime;

	UPROPERTY(EditAnywhere)
	float SpawnDistance = 1000.f;

	UPROPERTY(EditAnywhere)
	UEnvQuery* FindSpotEQS;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
