// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ChickenCharacter.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class CHICKENMAYHEM_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:

	ASpawner();
	
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

	void Spawn();

	void SelectTimeSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn parameters")
	TSubclassOf<AChickenCharacter> ChickenClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn parameters")
	float MinTimeSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn parameters")
	float MaxTimeSpawn;

private:

	FTimerHandle TimerSpawn;
	float TimeSpawn;
};
