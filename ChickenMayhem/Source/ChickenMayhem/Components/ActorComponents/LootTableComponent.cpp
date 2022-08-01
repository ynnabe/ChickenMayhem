// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorComponents/LootTableComponent.h"


float ULootTableComponent::CalculateSum()
{
	TArray<float> ValueArray;
	float RunningTotal = 0.0f;
	Items.GenerateValueArray(ValueArray);
	for(float Value : ValueArray)
	{
		RunningTotal = RunningTotal + Value;
	}

	return RunningTotal;
}

TSubclassOf<AInteractiveActor> ULootTableComponent::ChooseLoot()
{
	TSubclassOf<AInteractiveActor> Result;
	float RandomValue = FMath::RandRange(0.0f, TotalValue);
	TArray<TSubclassOf<AInteractiveActor>> Keys;
	Items.GenerateKeyArray(Keys);
	for(TSubclassOf<AInteractiveActor> InteractiveActor : Keys)
	{
		float* Value = Items.Find(InteractiveActor);
		if(RandomValue < *Value)
		{
			Result = InteractiveActor;
			break;
		}

		RandomValue = RandomValue - *Value;
	}

	return Result;
}

