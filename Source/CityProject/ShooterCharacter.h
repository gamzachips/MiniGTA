
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterBase.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class CITYPROJECT_API AShooterCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AShooterCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetHUDCrosshairs(float DeltaTIme);

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartRun();
	void StopRun();
	void Shoot();
	void StartAiming();
	void EndAiming();


	const float SpringArmDefaultLength = 200.f;
	const float SpringArmAimingLength = 120.f;

protected:
	

	AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

private:
	class AShooterPlayerController* Controller;
	class AShooterHUD* HUD;
	
};
