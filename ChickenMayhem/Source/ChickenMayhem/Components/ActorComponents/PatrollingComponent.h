// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"

class APatrolPath;

UENUM()
enum class EPathType : uint8
{
	Circle,
	PingPong
};

USTRUCT(BlueprintType)
struct FPathInfo
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Path")
	EPathType PathType = EPathType::Circle;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Path")
	APatrolPath* PatrolPath;

	bool bIsGoingBack = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHICKENMAYHEM_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void SelectRandomPathType();
	void SelectClosestPath();
	FVector SelectClosestWayPoint();
	FVector SelectNextWayPoint();
	bool CanPatrol() const;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Patrol parameters")
	FPathInfo PatrolInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patrol parameters")
	TSubclassOf<APatrolPath> PathClass;
	
private:
	int32 CurrentWayPointIndex = -1;
};
