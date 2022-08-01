// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactive/TimeIncreaseActor.h"

#include "Characters/BaseCharacter.h"

void ATimeIncreaseActor::BeginPlay()
{
	Super::BeginPlay();
	Minutes = FMath::RandRange(MinMinuts, MaxMinuts);
	Seconds = FMath::RandRange(MinSeconds, MaxSeconds);
}

void ATimeIncreaseActor::InteractFinished()
{
	Super::InteractFinished();
	ABaseCharacter* BaseCharacter = GetBaseCharacter();
	BaseCharacter->IncreaseTime(Minutes, Seconds);
	BaseCharacter->PlayPickUpSound(EPickUpSound::IncreaseTime);
	Destroy();
}
