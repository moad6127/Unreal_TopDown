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


void UEnemySpawnComponent::EnemyDeath(AEnemy* DeadEnemy)
{
	if (SpawnedEnemies.Contains(DeadEnemy))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyDeathFuncCall!!"));

		SpawnedEnemies.Remove(DeadEnemy);
	}
}

void UEnemySpawnComponent::GetSpawnLocation()
{
	if (FindSpotEQS)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetSpawnLocation!!"));

		FEnvQueryRequest QueryRequest(FindSpotEQS, GetOwner());
		QueryRequest.Execute(EEnvQueryRunMode::AllMatching, FQueryFinishedSignature::CreateUObject(this, &UEnemySpawnComponent::SpawnEnemy));
	}
}

void UEnemySpawnComponent::SpawnEnemy(TSharedPtr<FEnvQueryResult> result)
{
	if (result->IsSuccessful())
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnEnemy!!"));
		int32 NumEnemyClasses = EnemyClasses.Num();
		if (NumEnemyClasses > 0)
		{
			TArray<FVector> OutLocaitons;
			result->GetAllAsLocations(OutLocaitons);
			int32 RandLocaitonIndex = FMath::RandRange(0, OutLocaitons.Num() - 1);
			FVector SpawnLocation = OutLocaitons[RandLocaitonIndex];
			FTransform Transform(SpawnLocation);
			int32 Selection = FMath::RandRange(0, NumEnemyClasses - 1);
			SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClasses[Selection], Transform);
			//SpawnedEnemy->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnSpawn();
				SpawnedEnemies.AddUnique(SpawnedEnemy);
			}
		}
	}
}



void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	OnEnemyDeath.AddDynamic(this, &UEnemySpawnComponent::EnemyDeath);

}



void UEnemySpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

