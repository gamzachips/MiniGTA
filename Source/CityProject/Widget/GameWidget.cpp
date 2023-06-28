// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"
#include "Components/ProgressBar.h"
#include "../PlayerCharacter.h"

UGameWidget::UGameWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameWidget::SetHPBar(float MaxHP, float HP)
{
	if (HPBar)
		HPBar->SetPercent(HP / MaxHP);
}

void UGameWidget::SetStaminaBar(float MaxStamina, float Stamina)
{
	if (StaminaBar)
		StaminaBar->SetPercent(Stamina / MaxStamina);
}
