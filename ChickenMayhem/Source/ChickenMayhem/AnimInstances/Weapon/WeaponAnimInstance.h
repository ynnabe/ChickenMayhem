// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WeaponAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void PlayFireAnimation();
	void PlayReloadAnimation(float& MontageDuration);

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montages")
	UAnimMontage* FireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montages")
	UAnimMontage* ReloadMontage;
	
};
