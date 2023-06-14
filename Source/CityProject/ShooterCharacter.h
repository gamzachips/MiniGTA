
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UENUM(BlueprintType)
enum class ShooterState : uint8
{
	None,
	Aiming,
	Die
};

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
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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
	void Die();

public:
	ShooterState GetState() { return State; }

private:
	UPROPERTY(EditAnywhere)
		ShooterState State = ShooterState::None;

	const float WalkSpeed = 1.0;
	const float RunSpeed = 2.0;
	const float SpringArmDefaultLength = 200.f;
	const float SpringArmAimingLength = 120.f;

private:
	float Speed = WalkSpeed;
private:
	class AShooterPlayerController* Controller;
	class AShooterHUD* HUD;
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
		float Health = MaxHealth;
};
