// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractiveActor.h"
#include "AmmoActor.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API AAmmoActor : public AInteractiveActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	int32 Ammo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ammo", meta=(ClampMin = 1, UIMin = 1))
	int32 MinAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ammo", meta=(ClampMin = 2, UIMin = 2))
	int32 MaxAmmo;
	
	virtual void InteractFinished() override;
	
};
