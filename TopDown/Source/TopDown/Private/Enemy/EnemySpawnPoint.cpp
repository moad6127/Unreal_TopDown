// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawnPoint.h"
#include "Enemy/Enemy.h"
#include "Components/SphereComponent.h"

AEnemySpawnPoint::AEnemySpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnSphere"));
	Sphere->SetSphereRadius(1000.f);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SetRootComponent(Sphere);

}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawnPoint::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEnemySpawnPoint::EndOverlap);
	
	StartSpawnEnemyTimer();
}

void AEnemySpawnPoint::SpawnEnemy()
{
	int32 NumEnemyClasses = EnemyClasses.Num();
	if (NumEnemyClasses > 0)
	{
		int32 Selection = FMath::RandRange(0, NumEnemyClasses - 1);
		SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClasses[Selection], GetActorTransform());
		SpawnedEnemy->OnSpawn();
		InRangeActor.AddUnique(SpawnedEnemy);
	}
}

void AEnemySpawnPoint::SpawnEnemyTimerFinished()
{
	SpawnEnemy();
}

void AEnemySpawnPoint::StartSpawnEnemyTimer()
{
	const float SpawnTime = FMath::FRandRange(SpawnEnemyTimeMin, SpawnEnemyTimeMax);
	GetWorldTimerManager().SetTimer(
		SpawnEnemyTimer,
		this,
		&AEnemySpawnPoint::SpawnEnemyTimerFinished,
		SpawnTime
	);
}

void AEnemySpawnPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InRangeActor.AddUnique(OtherActor);
}

void AEnemySpawnPoint::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InRangeActor.Remove(OtherActor);
	if (InRangeActor.Num() == 0)
	{
		StartSpawnEnemyTimer();
	}
}

void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

