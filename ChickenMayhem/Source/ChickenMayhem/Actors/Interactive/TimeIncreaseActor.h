// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractiveActor.h"
#include "TimeIncreaseActor.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API ATimeIncreaseActor : public AInteractiveActor
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

	virtual void InteractFinished() override;
	
	int32 Minutes;
	
	int32 Seconds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time parameters", meta=(ClampMin=0, UIMin=0))
	int32 MinMinuts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time parameters", meta=(ClampMin=0, UIMin=0))
	int32 MaxMinuts;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time parameters", meta=(ClampMin=0, UIMin=0, ClampMax=59, UIMax = 59))
	int32 MinSeconds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time parameters", meta=(ClampMin=0, UIMin=0, ClampMax=59, UIMax = 59))
	int32 MaxSeconds;
	
};
