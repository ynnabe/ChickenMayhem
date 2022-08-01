// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/ChickenCharacter.h"
#include "ChickenAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UChickenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Speed")
	float WalkSpeed;
	

private:

	TWeakObjectPtr<AChickenCharacter> CachedChickenCharacter;
	
};
