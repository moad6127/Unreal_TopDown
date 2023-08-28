// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack/Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Kismet/Gameplaystatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	

}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	PlayAttackSound();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::CollisionBoxOverlap);
}

void AProjectile::CollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (OtherActor->ActorHasTag("Enemy"))
	{
		if (OwnerCharacter)
		{
			AController* OwnerController = OwnerCharacter->Controller;
			if (OwnerController)
			{
				UE_LOG(LogTemp, Warning, TEXT("ApplyDamage : %f"), Damage);
				UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, UDamageType::StaticClass());
			}
		}
		if (HitInterface)
		{
			UE_LOG(LogTemp, Warning, TEXT("AttackOverlap"));
			HitInterface->GetHit(SweepResult.ImpactPoint);
		}
		Destroy();
	}
}

void AProjectile::PlayAttackSound()
{
	if (AttckSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			AttckSound,
			GetActorLocation());
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

