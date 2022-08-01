// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "InteractiveActor.generated.h"

class ABaseCharacter;

UCLASS()
class CHICKENMAYHEM_API AInteractiveActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AInteractiveActor();

	virtual void Interact(ABaseCharacter* Character) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	ABaseCharacter* GetBaseCharacter() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Moving")
	UCurveFloat* MovingCurveUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Moving")
	UCurveFloat* MovingCurveToPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Moving")
	float Height;

	UFUNCTION()
	virtual void MoveUp(float Value);

	UFUNCTION()
	virtual void MoveUpFinished();

	UFUNCTION()
	virtual void MoveToPlayer(float Value);

	UFUNCTION()
	virtual void InteractFinished();
	
private:
	
	FTimeline TimelineUp;
	FTimeline TimelineToPlayer;

	FVector FinishedUpLoc;

	TWeakObjectPtr<ABaseCharacter> CachedBaseCharacter;
};
