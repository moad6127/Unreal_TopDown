
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/HitInterface.h"
#include "TopDownCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class APlayerController;
class AProjectile;
class USphereComponent;
class AEnemy;
class UAttributeComponent;
class UTopDownOverlay;

UCLASS()
class TOPDOWN_API ATopDownCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ATopDownCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetHit(const FVector& ImpactPoint) override;
	void GetEXPPoint(float EXPPoint);
protected:
	virtual void BeginPlay() override;

	void InitializeTopDownOverlay();

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* CharacterContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;

	void Move(const FInputActionValue& Value);
	void ShowMouseCurser();

	void Attack();
	void SpawnProjectile();


private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* EnemyRadiusSphereComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupSphereComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	TArray<AActor*> EnemyInRange;

	UPROPERTY(VisibleAnywhere)
	AActor* CombatTarget;

	UPROPERTY()
	APlayerController* TopDownController;

	UPROPERTY()
	UTopDownOverlay* TopDownOverlay;

	UPROPERTY(EditAnywhere, Category = "Projectile Class")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackDamage = 15.f;

	FTimerHandle AttackTimer;
	bool bCanAttack = true;

	void StartAttackTimer();
	void AttackTimerFinished();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void PickupCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetCombatTarget();

public:	

};
