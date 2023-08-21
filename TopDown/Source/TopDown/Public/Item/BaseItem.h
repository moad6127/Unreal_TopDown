// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"


class USphereComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class TOPDOWN_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);


	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;


	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;

public:	


};
