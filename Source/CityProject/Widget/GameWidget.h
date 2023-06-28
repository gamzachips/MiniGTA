// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class CITYPROJECT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void SetHPBar(float MaxHP, float HP);
	void SetStaminaBar(float MaxStamina, float Stamina);

private:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;

};
