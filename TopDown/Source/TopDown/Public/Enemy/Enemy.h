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
class AEXPItem;
class AGoldItem;
class UUserWidget;

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
	void OnSpawn();
	void SetController(AController* InputController);
protected:
	virtual void BeginPlay() override;

	void Die();
	void SetAIController();
	void Attack();

	void PlayHitReactMontage();

	void PlayDeathMontage();
	void MoveToCharacter();

	void SpawnParticle(const FVector& ImpactPoint);
	void SpawnEXP();
	void SpawnGold();
	void SpawnDrop();

	void ShowHitNumer();
	void StoreHitNumber(UUserWidget* HitNumber, FVector Location);

	UFUNCTION()
	void DestroyHitNumber(UUserWidget* HitNumber);

	void UpdateHitNumbers();
	
	/**
	* AI Controll
	*/
	UPROPERTY(VisibleAnywhere)
	AAIController* EnemyController;

	UPROPERTY(VisibleAnywhere)
	ATopDownCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

private:
	
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere)
	UEnemyHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* AttackDamageRange;

	UPROPERTY(EditAnywhere, Category = DropItem)
	TSubclassOf<AEXPItem> EXPClass;

	UPROPERTY(EditAnywhere, Category = DropItem)
	TSubclassOf<AGoldItem> GoldClass;

	//floating Damage
	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<UUserWidget> HitNumberWidgetClass;

	UPROPERTY()
	UUserWidget* HitNumberWidget;

	UPROPERTY(VisibleAnywhere)
	TMap<UUserWidget*, FVector> HitNumbers;

	UPROPERTY(EditAnywhere)
	float HitNumberDestroyTime = 1.5f;


	UPROPERTY(EditAnywhere, Category = DropItem)
	float EnemyEXP = 30.f;

	UPROPERTY(EditAnywhere, Category = DropItem)
	int32 EnemyGold = 1;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;
	
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
