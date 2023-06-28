// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CITYPROJECT_API APlayerCharacter : public AShooterCharacter
{
	GENERATED_BODY()

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

protected:
	class AShooterPlayerController* Controller;
	class AShooterHUD* HUD;

	const float SpringArmDefaultLength = 200.f;
	const float SpringArmAimingLength = 120.f;

	const float MaxHP = 100.f;
	const float MaxStamina = 100.f;

	float HP = MaxHP;
	float Stamina = MaxStamina;


	//UI
protected:
	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<class UGameWidget> WidgetClass;
	UPROPERTY()
		class UGameWidget* GameUI;

};
