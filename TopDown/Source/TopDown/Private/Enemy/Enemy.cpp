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
#include "HUD/HitNumberWidget.h"
#include "Item/EXPItem.h"
#include "Item/GoldItem.h"
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

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetAIController();
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
	if (EnemyController)
	{
		EnemyController->StopMovement();
		EnemyController->ClearFocus(EAIFocusPriority::Gameplay);
	}
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackDamageRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnDrop();
	SetLifeSpan(2.f);
}

void AEnemy::SetAIController()
{
	if (EnemyController == nullptr)
	{
		EnemyController = Cast<AAIController>(GetController());
	}
}

void AEnemy::Attack()
{
	if (bCanAttack && CombatTarget)
	{
		bCanAttack = false;
		StartAttackTimer();
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
	SetAIController();
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

void AEnemy::SpawnEXP()
{
	UWorld* World = GetWorld();
	if (World && EXPClass)
	{
		const FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
		AEXPItem* EXP = World->SpawnActor<AEXPItem>(EXPClass, SpawnLocation, GetActorRotation());
		if (EXP)
		{
			EXP->SetEXP(EnemyEXP);
			EXP->SetOwner(this);
		}
	}

}

void AEnemy::SpawnGold()
{
	UWorld* World = GetWorld();
	if (World && GoldClass)
	{
		const FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
		AGoldItem* Gold = World->SpawnActor<AGoldItem>(GoldClass, SpawnLocation, GetActorRotation());

		if (Gold)
		{
			Gold->SetGold(EnemyGold);
			Gold->SetOwner(this);
		}
	}
}

void AEnemy::SpawnDrop()
{
	int32 RandomValue = FMath::RandRange(0, 100);
	UE_LOG(LogTemp, Warning, TEXT("RandomValue : %d"),RandomValue);
	if (RandomValue <= 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnGold"));

		SpawnGold();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn EXP"));

		SpawnEXP();
	}
}

void AEnemy::ShowHitNumer()
{
	if (HitNumberWidgetClass)
	{
		HitNumberWidget = CreateWidget<UHitNumberWidget>(GetWorld(), HitNumberWidgetClass);
		if (HitNumberWidget)
		{
			FVector WorldLocation = GetActorLocation();
			FVector2D ScreenLocaiton;

			UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WorldLocation, ScreenLocaiton);
			HitNumberWidget->SetPositionInViewport(ScreenLocaiton);
			HitNumberWidget->AddToViewport();
			StoreHitNumber(HitNumberWidget, WorldLocation);
			
		}
	}
}

void AEnemy::StoreHitNumber(UHitNumberWidget* HitNumber, FVector Location)
{
	HitNumbers.Add(HitNumber, Location);

	FTimerHandle HitNumberTimer;
	FTimerDelegate HitNumberDelegate;

	HitNumberDelegate.BindUFunction(this, FName("DestroyHitNumber"), HitNumber);

	GetWorld()->GetTimerManager().SetTimer(
		HitNumberTimer,
		HitNumberDelegate,
		HitNumberDestroyTime,
		false);
}

void AEnemy::DestroyHitNumber(UHitNumberWidget* HitNumber)
{
	HitNumbers.Remove(HitNumber);
	HitNumber->RemoveFromParent();
}

void AEnemy::UpdateHitNumbers()
{
	for (auto& HitPair : HitNumbers)
	{
		UHitNumberWidget* HitNumber{ HitPair.Key };
		const FVector Location{ HitPair.Value };
		FVector2D ScreenPosition;

		UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), Location, ScreenPosition);
		HitNumber->SetPositionInViewport(ScreenPosition);
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

		Attack();
	}
}

void AEnemy::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CombatTarget = nullptr;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DeathPose == EDeathPose::EDP_Alive)
	{
		MoveToCharacter();
	}
	UpdateHitNumbers();
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
	ShowHitNumer();
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

	}
	return DamageAmount;
}

void AEnemy::OnSpawn()
{
	SetAIController();
	MoveToCharacter();
}

void AEnemy::SetController(AController* InputController)
{
	if (EnemyController == nullptr)
	{
		EnemyController = Cast<AAIController>(InputController);
	}
}

