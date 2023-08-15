// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
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
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MoveToCharacter();
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
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
	SetLifeSpan(1.f);
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
		MoveRequest.SetAcceptanceRadius(15.f);
		FNavPathSharedPtr NavPath;
		EnemyController->MoveTo(MoveRequest, &NavPath);
	}
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
	UE_LOG(LogTemp, Warning, TEXT("GetHit"));
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
	if (Attributes && Attributes->IsAlive())
	{
		PlayHitReactMontage();
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

