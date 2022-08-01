// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactive/AmmoActor.h"

#include "Characters/BaseCharacter.h"


void AAmmoActor::BeginPlay()
{
	Super::BeginPlay();
	Ammo = FMath::RandRange(MinAmmo, MaxAmmo);
}

void AAmmoActor::InteractFinished()
{
	Super::InteractFinished();
	ABaseCharacter* Player = GetBaseCharacter();
	Player->PlayPickUpSound(EPickUpSound::Ammo);
	Player->AddAvailableAmmo(Ammo);
	Destroy();
}
