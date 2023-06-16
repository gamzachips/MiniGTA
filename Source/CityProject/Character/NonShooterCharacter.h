
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ShooterCharacter.h"
#include "NonShooterCharacter.generated.h"

UCLASS()
class CITYPROJECT_API ANonShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANonShooterCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	CharacterState GetState() { return State; }

protected:
	UPROPERTY(EditAnywhere)
		CharacterState State = CharacterState::None;

	const float WalkSpeed = 1.0;
	const float RunSpeed = 2.0;

	float Speed = WalkSpeed;
};
