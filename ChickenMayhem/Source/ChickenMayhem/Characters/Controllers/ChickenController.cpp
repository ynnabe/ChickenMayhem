// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/ChickenController.h"
#include "ChickenMayhemTypes.h"
#include "ChickenMayhem/Components/ActorComponents/PatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void AChickenController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(IsValid(InPawn))
	{
		CachedChickenCharacter = StaticCast<AChickenCharacter*>(InPawn);
		RunBehaviorTree(CachedChickenCharacter->GetBehaviorTree());
		SetupPatrolling();
	}
	else
	{
		CachedChickenCharacter = nullptr;
	}
}

void AChickenController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if(!Result.IsSuccess())
	{
		return;
	}
	TryMoveToNextTarget();
}

void AChickenController::SetupPatrolling()
{
	UPatrollingComponent* PatrollingComponent = CachedChickenCharacter->GetPatrollingComponent();
	if(!PatrollingComponent->CanPatrol())
	{
		PatrollingComponent->SelectClosestPath();
		PatrollingComponent->SelectRandomPathType();
	}

	FVector ClosestWayPoint = PatrollingComponent->SelectClosestWayPoint();
	if(IsValid(Blackboard))
	{
		Blackboard->SetValueAsVector(BB_NextLocation, ClosestWayPoint);
	}
	bIsPatrol = true;
}

void AChickenController::TryMoveToNextTarget()
{
	UPatrollingComponent* PatrollingComponent = CachedChickenCharacter->GetPatrollingComponent();
	if(PatrollingComponent->CanPatrol())
	{
		FVector NextWayPoint = bIsPatrol ? PatrollingComponent->SelectNextWayPoint() : PatrollingComponent->SelectClosestWayPoint();
		if(IsValid(Blackboard))
		{
			Blackboard->SetValueAsVector(BB_NextLocation, NextWayPoint);
		}
	}
}

bool AChickenController::IsTargetReached(FVector TargetLocation)
{
	return false;
}
