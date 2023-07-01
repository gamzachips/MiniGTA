// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPeopleController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIPeopleController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree != nullptr)
		RunBehaviorTree(AIBehaviorTree);

	FVector ActorStartLocation = GetPawn()->GetActorLocation();

	GetBlackboardComponent()->SetValueAsVector(TEXT("ActorStartLocation"), ActorStartLocation);

	FVector TargetLocation = ActorStartLocation + CharacterWalkDistance;
	GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);

}
