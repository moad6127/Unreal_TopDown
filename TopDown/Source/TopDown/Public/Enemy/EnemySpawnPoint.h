// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"


class AEnemy;
class USphereComponent;


UCLASS()
class TOPDOWN_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawnPoint();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AEnemy>> EnemyClasses;

	UPROPERTY()
	AEnemy* SpawnedEnemy;

	void SpawnEnemy();
	void SpawnEnemyTimerFinished();

	UFUNCTION()
	void StartSpawnEnemyTimer();
private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	FTimerHandle SpawnEnemyTimer;

	UPROPERTY(EditAnywhere)
	float SpawnEnemyTimeMin;

	UPROPERTY(EditAnywhere)
	float SpawnEnemyTimeMax;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> InRangeActor;


	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

};
