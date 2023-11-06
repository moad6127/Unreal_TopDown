// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class ATopDownCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	friend ATopDownCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ATopDownCharacter* Character;
	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float EXP;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxEXP;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float HealthRegen = 0.1f;

	

public:	

	void ReceiveDamage(float Damage);
	void GetEXPPoint(float GetEXPPoint);
	float GetHealthPercent();
	float GetEXPPercent();
	bool IsAlive();
	bool IsLevelUp();
	void SetGold(int32 GoldCount);
	void SetMaxHealth(float SetMaxHealth);
	void SetMaxEXP(float SetMaxEXP);
	void SetHealthRegen(float SetHealing);
	void TickHealthRegen(float DeltaTime);

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetEXP() const { return EXP; }
	FORCEINLINE float GetMaxEXP() const { return MaxEXP; }
	FORCEINLINE int32 GetGold() const { return Gold; }
};
