
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class CITYPROJECT_API AShooterCharacter : public ACharacter
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

public:
	bool GetIsAiming() { return bIsAiming; }

private:
	
	const float WalkSpeed = 1.0;
	const float RunSpeed = 2.0;

private:
	float Speed = WalkSpeed;
	bool bIsAiming = false;

private:
	class AShooterPlayerController* Controller;
	class AShooterHUD* HUD;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY()
		AGun* Gun; 
};
