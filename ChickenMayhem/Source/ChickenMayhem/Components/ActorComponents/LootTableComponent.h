// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/InteractiveActor.h"
#include "Components/ActorComponent.h"
#include "LootTableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHICKENMAYHEM_API ULootTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	float CalculateSum();
	TSubclassOf<AInteractiveActor> ChooseLoot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn chances")
	TMap<TSubclassOf<AInteractiveActor>, float> Items;
	
	float TotalValue = 0.0f;
	
};
