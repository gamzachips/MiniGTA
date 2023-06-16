
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ShooterCharacter.h"
#include "NonShooterCharacter.generated.h"

UCLASS()
class CITYPROJECT_API ANonShooterCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	ANonShooterCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
