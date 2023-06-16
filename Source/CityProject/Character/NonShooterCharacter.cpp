
#include "NonShooterCharacter.h"

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

}

void ANonShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

