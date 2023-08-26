// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Character/TopDownCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Component/AttributeComponent.h"
#include "HUD/EnemyHealthBarComponent.h"
#include "DrawDebugHelpers.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(true);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributesComponent"));

	HealthBarWidget = CreateDefaultSubobject<UEnemyHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	AttackDamageRange = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyRadiusSphereComponent"));
	AttackDamageRange->SetupAttachment(GetRootComponent());
	AttackDamageRange->SetSphereRadius(15.f);
	AttackDamageRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackDamageRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MoveToCharacter();
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	AttackDamageRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlap);
	AttackDamageRange->OnComponentEndOverlap.AddDynamic(this, &AEnemy::EndOverlap);
	Tags.Add(FName("Enemy"));

}

void AEnemy::Die()
{
	PlayDeathMontage();

	EnemyController->StopMovement();
	EnemyController->ClearFocus(EAIFocusPriority::Gameplay);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackDamageRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(1.f);
}

void AEnemy::Attack()
{
	if (bCanAttack && CombatTarget)
	{
		bCanAttack = false;
		StartAttackTimer();
		UE_LOG(LogTemp, Warning, TEXT("CharacterGetDamage : %f"), AttackDamage);
		UGameplayStatics::ApplyDamage(CombatTarget, AttackDamage, GetController(), this, UDamageType::StaticClass());
	}
}

void AEnemy::PlayHitReactMontage()
{
	UAnimInstance* AnimInstace = GetMesh()->GetAnimInstance();
	if (AnimInstace && HitReactMontage)
	{
		AnimInstace->Montage_Play(HitReactMontage);
	}
}

void AEnemy::PlayDeathMontage()
{
	UAnimInstance* AnimInstace = GetMesh()->GetAnimInstance();
	if (AnimInstace && DeathMontage)
	{
		DeathPose = EDeathPose::EDP_Death;
		AnimInstace->Montage_Play(DeathMontage);
	}
}

void AEnemy::MoveToCharacter()
{
	if (EnemyController == nullptr)
	{
		EnemyController = Cast<AAIController>(GetController());
	}
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<ATopDownCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}

	if (EnemyController && PlayerCharacter)
	{
		EnemyController->SetFocus(PlayerCharacter);
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(PlayerCharacter);
		MoveRequest.SetAcceptanceRadius(30.f);
		FNavPathSharedPtr NavPath;
		EnemyController->MoveTo(MoveRequest, &NavPath);
	}
}

void AEnemy::SpawnParticle(const FVector& ImpactPoint)
{
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}
}

void AEnemy::StartAttackTimer()
{
	if (CombatTarget)
	{
		GetWorldTimerManager().SetTimer(
			AttackTimer,
			this,
			&AEnemy::AttackTimerFinished,
			0.5f
		);
	}
}

void AEnemy::AttackTimerFinished()
{
	bCanAttack = true;
	Attack();
}

void AEnemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("PlayerCharacter"))
	{
		CombatTarget = OtherActor;
		UE_LOG(LogTemp, Warning, TEXT("CharacterInEnemyAttackRange"));

		Attack();
	}
}

void AEnemy::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CombatTarget = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("CharacterOutEnemyAttackRange"));
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DeathPose == EDeathPose::EDP_Alive)
	{
		MoveToCharacter();
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit(const FVector& ImpactPoint)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
	if (Attributes && Attributes->IsAlive())
	{
		PlayHitReactMontage();
		SpawnParticle(ImpactPoint);
	}
	else
	{
		Die();
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes && HealthBarWidget)
	{
		Attributes->ReceiveDamage(DamageAmount);
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
		UE_LOG(LogTemp, Warning, TEXT("TakeDamage : %f"),DamageAmount);
	}
	return DamageAmount;
}

