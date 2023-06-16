
#include "CharacterBase.h"

ACharacterBase::ACharacterBase()
{
 
	PrimaryActorTick.bCanEverTick = true;

}


void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}


void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("TEST"));

	DamageToApplied = FMath::Min(Health, DamageToApplied);
	Health -= DamageToApplied;
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);

	if (Health <= 0.00000)
		Die();

	return DamageToApplied;
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::Die()
{
	State = CharacterState::Die;
}
