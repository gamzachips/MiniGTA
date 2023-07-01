// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShooterHUD.h"
#include "Widget/GameWidget.h"
#include "Gun.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->Possess(this);
		Controller = Cast<AShooterPlayerController>(PlayerController);
	}

	if (WidgetClass != nullptr)
	{
		GameUI = Cast<UGameWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (GameUI)
			GameUI->AddToViewport();
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetHUDCrosshairs(DeltaTime);

	
	if (State == CharacterState::Running)
	{
		Stamina = FMath::Max(0, Stamina - 10 * DeltaTime);
		if (Stamina == 0)
			StopRun();
	}
	else
	{
		Stamina = FMath::Min(MaxStamina, Stamina + 10 * DeltaTime);
	}

	GameUI->SetStaminaBar(MaxStamina, Stamina);
	GameUI->SetHPBar(MaxHP, HP);
	
}



void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &APlayerCharacter::StartRun);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &APlayerCharacter::StopRun);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &APlayerCharacter::EndAiming);
}

void APlayerCharacter::SetHUDCrosshairs(float DeltaTIme)
{
	if (this->Controller == nullptr)
	{
		return;
	}

	Controller = Controller == nullptr ? Cast<AShooterPlayerController>(this->Controller) : Controller;

	if (Controller)
	{
		HUD = HUD == nullptr ? Cast<AShooterHUD>(Controller->GetHUD()) : HUD;

		if (HUD)
		{
			FHUDPackage HUDPackage;
			HUDPackage.CrosshairsCenter = Gun->CrosshairsCenter;
			HUDPackage.CrosshairsLeft = Gun->CrosshairsLeft;
			HUDPackage.CrosshairsRight = Gun->CrosshairsRight;
			HUDPackage.CrosshairsTop = Gun->CrosshairsTop;
			HUDPackage.CrosshairsBottom = Gun->CrosshairsBottom;
			HUD->SetHUDPackage(HUDPackage);
		}
	}
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * Speed);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * Speed);
}

void APlayerCharacter::StartRun()
{
	State = CharacterState::Running;
		Speed = RunSpeed;
}

void APlayerCharacter::StopRun()
{
	State = CharacterState::None;
	Speed = WalkSpeed;
}

void APlayerCharacter::Shoot()
{
	if (State == CharacterState::Aiming)
		Gun->PullTrigger();
}

void APlayerCharacter::StartAiming()
{
	State = CharacterState::Aiming;
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	SpringArm->TargetArmLength = SpringArmAimingLength;
}

void APlayerCharacter::EndAiming()
{
	State = CharacterState::None;
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	SpringArm->TargetArmLength = SpringArmDefaultLength;
}

