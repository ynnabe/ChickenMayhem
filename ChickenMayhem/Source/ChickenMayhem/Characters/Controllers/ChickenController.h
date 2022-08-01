// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/ChickenCharacter.h"
#include "ChickenController.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API AChickenController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void SetPawn(APawn* InPawn) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	void SetupPatrolling();

private:
	void TryMoveToNextTarget();
	TWeakObjectPtr<AChickenCharacter> CachedChickenCharacter;

	bool IsTargetReached(FVector TargetLocation);
	bool bIsPatrol = true;
	
};
