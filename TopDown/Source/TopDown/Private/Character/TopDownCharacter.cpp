// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TopDownCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Attack/Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AttributeComponent.h"
#include "HUD/TopDownHUD.h"
#include "HUD/TopDownOverlay.h"


ATopDownCharacter::ATopDownCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;


	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	EnemyRadiusSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyRadiusSphereComponent"));
	EnemyRadiusSphereComponent->SetupAttachment(GetRootComponent());
	EnemyRadiusSphereComponent->SetSphereRadius(1000.f);
	EnemyRadiusSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	EnemyRadiusSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributesComponent"));
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Attack();
}

void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::Attack);
	}
}

float ATopDownCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes &&TopDownOverlay)
	{
		Attributes->ReceiveDamage(DamageAmount);
		TopDownOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
		TopDownOverlay->SetHealth(Attributes->GetHealth());
		UE_LOG(LogTemp, Warning, TEXT("CharacterTakeDamage : %f"), DamageAmount);
	}
	return DamageAmount;
}

void ATopDownCharacter::GetHit(const FVector& ImpactPoint)
{

}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(CharacterContext, 0);
		}
	}
	EnemyRadiusSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATopDownCharacter::BeginOverlap);
	EnemyRadiusSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATopDownCharacter::EndOverlap);
	ShowMouseCurser();
	Tags.Add(FName("PlayerCharacter"));
	InitializeTopDownOverlay();
}

void ATopDownCharacter::InitializeTopDownOverlay()
{
	if (TopDownController == nullptr)
	{
		TopDownController = Cast<APlayerController>(GetController());
	}
	if (TopDownController)
	{
		ATopDownHUD* TopDownHUD = Cast<ATopDownHUD>(TopDownController->GetHUD());
		if (TopDownHUD)
		{
			TopDownOverlay = TopDownHUD->GetTopDownOverlay();
			if (TopDownOverlay && Attributes)
			{
				TopDownOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				TopDownOverlay->SetEXPBarPercent(Attributes->GetEXPPercent());
				TopDownOverlay->SetHealth(Attributes->GetHealth());
				TopDownOverlay->SetMaxHealt(Attributes->GetMaxHealth());
				TopDownOverlay->SetEXP(Attributes->GetEXP());
				TopDownOverlay->SetMAXEXP(Attributes->GetMaxEXP());
			}
		}
	}
}


void ATopDownCharacter::Move(const FInputActionValue& Value)
{

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector DirectionForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(DirectionForward, MovementVector.Y);

	const FVector DirectionRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(DirectionRight, MovementVector.X);
}

void ATopDownCharacter::ShowMouseCurser()
{
	TopDownController = Cast<APlayerController>(GetController());
	if (TopDownController)
	{
		TopDownController->bShowMouseCursor = true;
	}
}

void ATopDownCharacter::Attack()
{
	if (bCanAttack)
	{
		bCanAttack = false;
		StartAttackTimer();
		SetCombatTarget();
		SpawnProjectile();
	}
}

void ATopDownCharacter::SpawnProjectile()
{
	if (ProjectileClass)
	{
		APawn* InstigatorPawn = Cast<APawn>(GetOwner());
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = InstigatorPawn;
		

		FVector StartPoint = GetTransform().GetLocation();
		FRotator AttackRotation;
		if (CombatTarget)
		{
			FVector Target = CombatTarget->GetActorTransform().GetLocation() - StartPoint;
			AttackRotation = Target.Rotation();
		}
		else
		{
			AttackRotation = GetActorForwardVector().Rotation();
		}
		
		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* SpawnProjectile = World->SpawnActor<AProjectile>(
				ProjectileClass,
				StartPoint,
				AttackRotation,
				SpawnParams
				);
			if (SpawnProjectile)
			{
				SpawnProjectile->SetLifeSpan(10.f);
				SpawnProjectile->SetDamage(AttackDamage);
			}
		}
	}
}

void ATopDownCharacter::StartAttackTimer()
{
	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&ATopDownCharacter::AttackTimerFinished,
		1.f
	);
}

void ATopDownCharacter::AttackTimerFinished()
{
	bCanAttack = true;
	Attack();

}

void ATopDownCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		EnemyInRange.AddUnique(OtherActor);
	}

}

void ATopDownCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		EnemyInRange.Remove(OtherActor);
	}
	if (CombatTarget == OtherActor)
	{
		CombatTarget = nullptr;
	}
}

void ATopDownCharacter::SetCombatTarget()
{
	const FVector Location = GetActorLocation();
	FVector ClosestEnmeyLocationDistance(1000.f);
	AActor* ClosestEnemy{};
	for (auto Enemy : EnemyInRange)
	{
		FVector DistanceToEnemy = Location - Enemy->GetActorLocation();
		if (DistanceToEnemy.Length() < ClosestEnmeyLocationDistance.Length())
		{
			ClosestEnemy = Enemy;
			ClosestEnmeyLocationDistance = DistanceToEnemy;
		}
	}
	CombatTarget = ClosestEnemy;
}





