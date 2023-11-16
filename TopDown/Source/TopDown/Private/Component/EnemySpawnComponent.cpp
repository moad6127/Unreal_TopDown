// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EnemySpawnComponent.h"
#include "Enemy/Enemy.h"
#include "Character/TopDownCharacter.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"


UEnemySpawnComponent::UEnemySpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemySpawnComponent::CheckTime(int32 Time)
{

}

void UEnemySpawnComponent::SpawnEnemy()
{

}



void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UEnemySpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

