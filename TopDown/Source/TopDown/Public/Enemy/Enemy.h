// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Character/CharacterType.h"
#include "Enemy.generated.h"

class AAIController;
class ATopDownCharacter;
class UAnimMontage;
class UAttributeComponent;
class UEnemyHealthBarComponent;
class USphereComponent;

UCLASS()
class TOPDOWN_API AEnemy : public ACharacter , public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	void Die();

	void Attack();

	void PlayHitReactMontage();

	void PlayDeathMontage();
	void MoveToCharacter();


	/**
	* AI Controll
	*/
	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY()
	ATopDownCharacter* PlayerCharacter;

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

private:
	
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere)
	UEnemyHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* AttackDamageRange;
	
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* DeathMontage;

	UPROPERTY(VisibleAnywhere)
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackDamage = 15.f;

	FTimerHandle AttackTimer;
	bool bCanAttack = true;

	void StartAttackTimer();
	void AttackTimerFinished();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	AAIController* GetEnemyController() { return EnemyController; }
	EDeathPose GetDeathPose() { return DeathPose; }
};
