
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"


UENUM(BlueprintType)
enum class CharacterState : uint8
{
	None,
	Aiming,
	Die
};

UCLASS()
class CITYPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	CharacterState GetState() { return State; }
	
protected:
	void Die();

protected:
	UPROPERTY(EditAnywhere)
		CharacterState State = CharacterState::None;

	const float WalkSpeed = 1.0;
	const float RunSpeed = 2.0;

	float Speed = WalkSpeed;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
		float Health = MaxHealth;
};
