// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAnimInstance.h"

void UWeaponAnimInstance::PlayFireAnimation()
{
	Montage_Play(FireMontage);
}

void UWeaponAnimInstance::PlayReloadAnimation(float& MontageDuration)
{
	MontageDuration = Montage_Play(ReloadMontage);
}

void UWeaponAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UWeaponAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
