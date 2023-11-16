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
#include "Kismet/GameplayStatics.h"
#include "Component/AttributeComponent.h"
#include "Component/EnemySpawnComponent.h"
#include "HUD/TopDownHUD.h"
#include "HUD/TopDownOverlay.h"
#include "Interface/PickupInterface.h"
#include "SaveGame/TopDownSaveGame.h"
#include "Controller/TopDownCharacterController.h"


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

	PickupSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphereComponent"));
	PickupSphereComponent->SetupAttachment(GetRootComponent());
	PickupSphereComponent->SetSphereRadius(150.f);
	PickupSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	PickupSphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributesComponent"));
	EnemySpawnComp = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Attack();
	SetTime();
}

void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::Attack);
		EnhancedInputComponent->BindAction(GamePauseAction, ETriggerEvent::Triggered, this, &ATopDownCharacter::GamePause);
	}

}

void ATopDownCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Attributes)
	{
		Attributes->Character = this;
	}
	if (EnemySpawnComp)
	{
		EnemySpawnComp->Character = this;
	}
}

float ATopDownCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ReceivedDamage = DamageAmount - (CharacterState.ArmorLevel * 1.f);
	if (Attributes &&TopDownOverlay)
	{
		Attributes->ReceiveDamage(ReceivedDamage);
		if (!Attributes->IsAlive())
		{
			Die();
		}
		TopDownOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
		TopDownOverlay->SetHealth(Attributes->GetHealth());
		UE_LOG(LogTemp, Warning, TEXT("CharacterTakeDamage : %f"), ReceivedDamage);
	}
	return ReceivedDamage;
}


void ATopDownCharacter::GetEXPPoint(float EXPPoint)
{
	if (Attributes && TopDownOverlay)
	{
		Attributes->GetEXPPoint(EXPPoint);
		if (Attributes->IsLevelUp())
		{
			LevelUp();
		}
		TopDownOverlay->SetEXP(Attributes->GetEXP());
		TopDownOverlay->SetEXPBarPercent(Attributes->GetEXPPercent());
	}
}

void ATopDownCharacter::GetGold(int32 GoldCount)
{
	if (Attributes && TopDownOverlay)
	{
		Attributes->SetGold(GoldCount);
		int32 Gold = Attributes->GetGold();
		TopDownOverlay->SetGoldText(Gold);
	}
}

void ATopDownCharacter::LevelUp()
{
	PlayerLevel = FMath::Clamp(PlayerLevel + 1, 1, 1000);
	TopDownController = TopDownController == nullptr ? Cast<ATopDownCharacterController>(GetController()) : TopDownController;

	if (Attributes && TopDownOverlay && TopDownController)
	{
		const float nowMaxEXP = Attributes->GetMaxEXP();
		Attributes->SetMaxEXP(nowMaxEXP * 1.5f);
		TopDownOverlay->SetMAXEXP(Attributes->GetMaxEXP());
		TopDownOverlay->SetLevel(PlayerLevel);
		TopDownController->LevelUp();
	}
}

void ATopDownCharacter::StateLevelUp(ECharacterState Oper)
{
	CharacterState.LevelUp(Oper);
}

void ATopDownCharacter::MaxHealthLevelUp()
{
	if (Attributes && TopDownOverlay)
	{
		float BaseMaxHealth{ 100.f };
		float MaxHealth = BaseMaxHealth + (CharacterState.HealthLevel * 20.f);
		Attributes->SetMaxHealth(MaxHealth);
		TopDownOverlay->SetMaxHealt(MaxHealth);
		SetHUDHealth();
	}
}

void ATopDownCharacter::MaxSpeedLevelUp()
{
	if (GetCharacterMovement())
	{
		float BaseMaxWalkSpeed{600.f};
		GetCharacterMovement()->MaxWalkSpeed = BaseMaxWalkSpeed + (CharacterState.SpeedLevel * 15.f);
	}
}

void ATopDownCharacter::SetHealthRegen()
{
	if (Attributes)
	{
		Attributes->SetHealthRegen(CharacterState.HealthRegenLevel * 0.1f);
	}
}

void ATopDownCharacter::SetHUDHealth()
{
	TopDownOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	TopDownOverlay->SetHealth(Attributes->GetHealth());
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
	PickupSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATopDownCharacter::PickupCompBeginOverlap);

	Tags.Add(FName("PlayerCharacter"));
	InitPlayerData();
	ShowMouseCurser();
	InitializeTopDownOverlay();
	SetPlayerData();
	StartSpawnEnemyTimer();
}

void ATopDownCharacter::InitializeTopDownOverlay()
{
	if (TopDownController == nullptr)
	{
		TopDownController = Cast<ATopDownCharacterController>(GetController());
	}
	if (TopDownController)
	{
		ATopDownHUD* TopDownHUD = Cast<ATopDownHUD>(TopDownController->GetHUD());
		if (TopDownHUD)
		{
			TopDownOverlay = TopDownHUD->GetTopDownOverlay();
			if (TopDownOverlay && Attributes)
			{
				TopDownOverlay->AddToViewport(1);
				TopDownOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				TopDownOverlay->SetEXPBarPercent(Attributes->GetEXPPercent());
				TopDownOverlay->SetHealth(Attributes->GetHealth());
				TopDownOverlay->SetMaxHealt(Attributes->GetMaxHealth());
				TopDownOverlay->SetEXP(Attributes->GetEXP());
				TopDownOverlay->SetMAXEXP(Attributes->GetMaxEXP());
				TopDownOverlay->SetLevel(PlayerLevel);
				TopDownOverlay->SetGoldText(Attributes->GetGold());
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
	TopDownController = Cast<ATopDownCharacterController>(GetController());
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

void ATopDownCharacter::GamePause()
{
	TopDownController = TopDownController == nullptr ? Cast<ATopDownCharacterController>(GetController()) : TopDownController;
	if (TopDownController)
	{
		TopDownController->GamePause();
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
				SpawnProjectile->SetDamage(AttackDamage * CharacterState.DamageLevel);
			}
		}
	}
}

void ATopDownCharacter::SetTime()
{
	uint32 MatchTime = FMath::CeilToInt(GetWorld()->GetTimeSeconds());

	if (CountDownInt != MatchTime)
	{
		if (TopDownOverlay)
		{
			TopDownOverlay->SetMatchCountDown(GetWorld()->GetTimeSeconds());
		}
	}
	CountDownInt = MatchTime;
}

void ATopDownCharacter::StartAttackTimer()
{
	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&ATopDownCharacter::AttackTimerFinished,
		AttackDelay - (CharacterState.AttackSpeedLevel * 0.1f)
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

void ATopDownCharacter::PickupCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupItem = Cast<IPickupInterface>(OtherActor);
	if (PickupItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemOverlap"));
		PickupItem->Pickup(this);
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

void ATopDownCharacter::SpawnEnemyTimerFinished()
{
	if (EnemySpawnComp)
	{
		EnemySpawnComp->GetSpawnLocation();
		StartSpawnEnemyTimer();
	}
}

void ATopDownCharacter::StartSpawnEnemyTimer()
{

	GetWorldTimerManager().ClearTimer(EnemySpawnTimer);

	const float SpawnTime = FMath::FRandRange(SpawnEnemyTimeMin, SpawnEnemyTimeMax);
	GetWorldTimerManager().SetTimer(
		EnemySpawnTimer,
		this,
		&ATopDownCharacter::SpawnEnemyTimerFinished,
		SpawnTime
	);
}

int32 ATopDownCharacter::GetPlayerGold()
{
	if (Attributes)
	{
		return Attributes->GetGold();
	}
	return 0;
}

void ATopDownCharacter::InitPlayerData()
{
	TopDownPlayerState = TopDownPlayerState == nullptr ? Cast<ATopDownPlayerState>(GetPlayerState()) : TopDownPlayerState;
	if (TopDownPlayerState == nullptr)
	{
		return;
	}
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(TopDownPlayerState->GetSaveSlotName(), 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}
	CharacterState = TopDownSaveGame->CharacterState;
	UE_LOG(LogTemp, Warning, TEXT("InitData"));
}

void ATopDownCharacter::SetPlayerData()
{
	MaxHealthLevelUp();
	MaxSpeedLevelUp();
	SetHealthRegen();
}

void ATopDownCharacter::SaveGame()
{
	TopDownPlayerState = TopDownPlayerState == nullptr ? Cast<ATopDownPlayerState>(GetPlayerState()) : TopDownPlayerState;

	if (TopDownPlayerState == nullptr)
	{
		return;
	}
	auto TopDownSaveGame = Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(TopDownPlayerState->GetSaveSlotName(), 0));
	if (TopDownSaveGame == nullptr)
	{
		TopDownSaveGame = GetMutableDefault<UTopDownSaveGame>();
	}
	TopDownSaveGame->Gold += Attributes->GetGold();
	UE_LOG(LogTemp, Warning, TEXT("SaveGold : %d "), TopDownSaveGame->Gold);
	if (UGameplayStatics::SaveGameToSlot(TopDownSaveGame, TopDownPlayerState->GetSaveSlotName(), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveData"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveDataFail!!!"));
	}
}

void ATopDownCharacter::Die()
{
	TopDownController = TopDownController == nullptr ? Cast<ATopDownCharacterController>(GetController()) : TopDownController;
	if (TopDownController)
	{
		TopDownController->ShowResultWidget();
	}
}





