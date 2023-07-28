// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TopDownCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Attack/Projectile.h"

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


	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	ShowMouseCurser();
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
		UE_LOG(LogTemp, Warning, TEXT("ShowCurser"));
		TopDownController->bShowMouseCursor = true;
	}
}

void ATopDownCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackButton"));

	SpawnProjectile();
}

void ATopDownCharacter::SpawnProjectile()
{
	UE_LOG(LogTemp, Warning, TEXT("FuncIn"));

	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("IfStattion"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = this;

		UWorld* World = GetWorld();
		if (World)
		{
			World->SpawnActor<AProjectile>(
				ProjectileClass,
				GetTransform().GetLocation(),
				GetActorForwardVector().Rotation(),
				SpawnParams
				);

			UE_LOG(LogTemp, Warning, TEXT("SpawnAttack"));
		}
	}
}





