
#include "ShooterCharacter.h"
#include "Gun.h"
#include "ShooterHUD.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/CharacterBase.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->Possess(this);
		Controller = Cast<AShooterPlayerController>(PlayerController);
	}
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetHUDCrosshairs(DeltaTime);
}



void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AShooterCharacter::StartRun);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AShooterCharacter::StopRun);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AShooterCharacter::StartAiming);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AShooterCharacter::EndAiming);
}

void AShooterCharacter::SetHUDCrosshairs(float DeltaTIme)
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


void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * Speed);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * Speed);
}

void AShooterCharacter::StartRun()
{
	Speed = RunSpeed;
}

void AShooterCharacter::StopRun()
{
	Speed = WalkSpeed;
}

void AShooterCharacter::Shoot()
{
	if(State == CharacterState::Aiming)
		Gun->PullTrigger();
}

void AShooterCharacter::StartAiming()
{
	State = CharacterState::Aiming;
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	SpringArm->TargetArmLength = SpringArmAimingLength;
}

void AShooterCharacter::EndAiming()
{
	State = CharacterState::None;
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();
	SpringArm->TargetArmLength = SpringArmDefaultLength;
}

