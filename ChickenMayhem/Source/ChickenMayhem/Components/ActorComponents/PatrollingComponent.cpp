// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorComponents/PatrollingComponent.h"

#include "Actors/Navigation/PatrolPath.h"
#include "Algo/MinElement.h"
#include "Kismet/GameplayStatics.h"

void UPatrollingComponent::SelectRandomPathType()
{
	int32 Index = FMath::RandRange(0 ,1);
	PatrolInfo.PathType = StaticCast<EPathType>(Index);
}

void UPatrollingComponent::SelectClosestPath()
{
	TArray<AActor*> PathArray;
	APatrolPath* Path;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PathClass, PathArray);

	auto ClosestPath = Algo::MinElementBy(PathArray, [&](const auto DamageActor){
	return (DamageActor->GetActorLocation() - GetOwner()->GetActorLocation()).SizeSquared();
	});

	if(ClosestPath)
	{
		Path = Cast<APatrolPath>(*ClosestPath);
		PatrolInfo.PatrolPath = Path;
	}
}

FVector UPatrollingComponent::SelectClosestWayPoint()
{
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	const TArray<FVector> WayPoints = PatrolInfo.PatrolPath->GetWayPoints();
	FTransform PathTransform = PatrolInfo.PatrolPath->GetActorTransform();

	FVector ClosestWayPoint;
	float MinSquaredDistance = FLT_MAX;

	for(int i = 0; i < WayPoints.Num(); i++)
	{
		FVector WayPointWorld = PathTransform.TransformPosition(WayPoints[i]);
		float CurrentDistance = (OwnerLocation - WayPointWorld).SizeSquared();
		if(CurrentDistance < MinSquaredDistance)
		{
			MinSquaredDistance = CurrentDistance;
			ClosestWayPoint = WayPointWorld;
			CurrentWayPointIndex = i;
		}
	}

	return ClosestWayPoint;
}

FVector UPatrollingComponent::SelectNextWayPoint()
{
	switch (PatrolInfo.PathType)
	{
	case EPathType::Circle:
		{
			++CurrentWayPointIndex;
			if(CurrentWayPointIndex == PatrolInfo.PatrolPath->GetWayPoints().Num())
			{
				CurrentWayPointIndex = 0;
			}
			break;
		}
	case EPathType::PingPong:
		{
			if(CurrentWayPointIndex == PatrolInfo.PatrolPath->GetWayPoints().Num() - 1)
			{
				PatrolInfo.bIsGoingBack = true;
			}
			else if(CurrentWayPointIndex == 0)
			{
				PatrolInfo.bIsGoingBack = false;
			}
			if(PatrolInfo.bIsGoingBack)
			{
				CurrentWayPointIndex--;
			}
			else
			{
				CurrentWayPointIndex++;
			}
			break;
		}
	}

	const TArray<FVector> WayPoints = PatrolInfo.PatrolPath->GetWayPoints();
	FTransform WayPointWorld = PatrolInfo.PatrolPath->GetActorTransform();
	FVector WayPoint = WayPointWorld.TransformPosition(WayPoints[CurrentWayPointIndex]);
	return WayPoint;
}

bool UPatrollingComponent::CanPatrol() const
{
	return IsValid(PatrolInfo.PatrolPath);
}
