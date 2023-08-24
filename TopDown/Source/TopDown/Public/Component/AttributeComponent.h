// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float EXP;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxEXP;

public:	

	void ReceiveDamage(float Damage);
	void GetEXP(float GetEXPPoint);
	float GetHealthPercent();
	float GetEXPPercent();
	bool IsAlive();
	bool LevelUp();
	void SetMaxHealth(float SetMaxHealth);
	void SetMaxEXP(float SetMaxEXP);
};
