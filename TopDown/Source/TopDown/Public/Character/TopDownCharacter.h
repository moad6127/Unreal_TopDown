
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TopDownCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class APlayerController;
class AProjectile;

UCLASS()
class TOPDOWN_API ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	virtual void BeginPlay() override;

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

	UPROPERTY()
	APlayerController* TopDownController;

	UPROPERTY(EditAnywhere, Category = "Projectile Class")
	TSubclassOf<AProjectile> ProjectileClass;

	FTimerHandle AttackTimer;
	bool bCanAttack = true;

	void StartAttackTimer();
	void AttackTimerFinished();
public:	

};
