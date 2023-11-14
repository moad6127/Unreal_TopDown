// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawnComponent.generated.h"

class ATopDownCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemySpawnComponent();
	friend ATopDownCharacter;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATopDownCharacter* Character;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
