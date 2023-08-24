

#include "Component/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
}

void UAttributeComponent::GetEXP(float GetEXPPoint)
{
	EXP = FMath::Clamp(EXP + GetEXPPoint, 0.f, MaxEXP);
}

float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetEXPPercent()
{
	return EXP / MaxEXP;
}

bool UAttributeComponent::IsAlive()
{
	return Health > 0.f;
}

bool UAttributeComponent::LevelUp()
{
	return EXP == MaxEXP;
}

void UAttributeComponent::SetMaxHealth(float SetMaxHealth)
{
	MaxHealth = SetMaxHealth;
	Health = MaxHealth;
}

void UAttributeComponent::SetMaxEXP(float SetMaxEXP)
{
	MaxEXP = SetMaxEXP;
	EXP = 0.f;
}


void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

