// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractiveActor.h"
#include "TimeSlowDownActor.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API ATimeSlowDownActor : public AInteractiveActor
{
	GENERATED_BODY()

protected:

	virtual void InteractFinished() override;
	
	
};
