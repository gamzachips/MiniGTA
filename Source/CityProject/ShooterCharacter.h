
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



protected:
	AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;


};
