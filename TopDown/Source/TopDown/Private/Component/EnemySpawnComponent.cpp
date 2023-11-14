// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EnemySpawnComponent.h"

UEnemySpawnComponent::UEnemySpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UEnemySpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

