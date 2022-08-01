// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Actors/Interactive/InteractiveActor.h"
#include "Components/ActorComponents/LootTableComponent.h"
#include "GameFramework/Character.h"
#include "ChickenCharacter.generated.h"

class UPatrollingComponent;
class UBehaviorTree;
UENUM()
enum class ETypeChicken
{
	None,
	Ground,
	Fly
};

UCLASS()
class CHICKENMAYHEM_API AChickenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AChickenCharacter();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;
	UPatrollingComponent* GetPatrollingComponent() const;
	bool IsAlive();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UPatrollingComponent* PatrollingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	ULootTableComponent* LootTableComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	UNiagaraSystem* DeathVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SFX")
	TArray<USoundBase*> DeathSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	int32 ScoreCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	ETypeChicken TypeChicken = ETypeChicken::None;
	
	virtual void BeginPlay() override;
	void SelectRandomDeathSound();
	TSubclassOf<AInteractiveActor> SelectRandomItem();
	void Death(AActor* DamageCauser);

private:

	float Health;

	void OnHealthChanged(AActor* DamageCauser);
	void OnDeath();
	FTimerHandle DeathTimer;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
												   AController* InstigatedBy, AActor* DamageCauser);

};
