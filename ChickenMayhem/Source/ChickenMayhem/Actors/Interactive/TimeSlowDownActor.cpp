// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactive/TimeSlowDownActor.h"
#include "Characters/BaseCharacter.h"

void ATimeSlowDownActor::InteractFinished()
{
	Super::InteractFinished();

	GetBaseCharacter()->StartSlowDownTime();
}
