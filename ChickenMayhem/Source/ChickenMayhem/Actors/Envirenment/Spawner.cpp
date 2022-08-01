// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Envirenment/Spawner.h"

#include "Gamemodes/BaseGameMode.h"


ASpawner::ASpawner()
{
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	ABaseGameMode* GameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	GameMode->OnGameStart.AddUObject(this, &ASpawner::Spawn);
}

void ASpawner::Spawn()
{
	AChickenCharacter* Chicken = GetWorld()->SpawnActor<AChickenCharacter>(ChickenClass, GetTransform());
	if(!IsValid(Chicken->Controller))
	{
		Chicken->SpawnDefaultController();
	}
	SelectTimeSpawn();
	GetWorld()->GetTimerManager().SetTimer(TimerSpawn, this, &ASpawner::Spawn, TimeSpawn, false);
}

void ASpawner::SelectTimeSpawn()
{
	TimeSpawn = FMath::RandRange(MinTimeSpawn, MaxTimeSpawn);
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

