
#include "NonShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../ShooterCharacter.h"

ANonShooterCharacter::ANonShooterCharacter()
{
 
	PrimaryActorTick.bCanEverTick = true;

}

void ANonShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANonShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	auto Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	double distance = FVector::Distance(Player->GetActorLocation(), this->GetActorLocation());
	
	if (distance <= 400)
	{
		if (Player->GetState() == CharacterState::Aiming)
			State = CharacterState::Surrender;
	}
	else if(State == CharacterState::Surrender)
	{
		State = CharacterState::None;
	}
}

void ANonShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

