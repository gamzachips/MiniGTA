// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPeopleController.generated.h"

/**
 * 
 */
UCLASS()
class CITYPROJECT_API AAIPeopleController : public AAIController
{
	GENERATED_BODY()

public:
	void MoveToLocation(const FVector& TargetLocation);

	
protected:
	virtual void BeginPlay() override;

private:
	//Behaviour trees
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehaviorTree;

	//Variables
	UPROPERTY(EditAnywhere)
		FVector CharacterWalkDistance;

};
