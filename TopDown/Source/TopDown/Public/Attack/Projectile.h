// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"\

class UBoxComponent;
class UProjectileMovementComponent;
class USoundBase;
UCLASS()
class TOPDOWN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void FireInDirection(const FVector& ShootDirection);


protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	USoundBase* AttckSound;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Damage;

	UFUNCTION()
	void CollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayAttackSound();
public:	
	FORCEINLINE void SetDamage(float GetDamage) { Damage = GetDamage; }
};
