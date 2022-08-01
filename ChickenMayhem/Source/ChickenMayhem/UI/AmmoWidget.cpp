// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"

#include "ChickenMayhem/Characters/BaseCharacter.h"

void UAmmoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ABaseCharacter* BaseCharacter = StaticCast<ABaseCharacter*>(GetOwningPlayerPawn());
	if(IsValid(BaseCharacter))
	{
		BaseCharacter->OnAmmoCountChangedDelegate.AddUObject(this, &UAmmoWidget::UpdateAmmo);
		BaseCharacter->OnAvailableAmmoCountChangedDelegate.AddUObject(this, &UAmmoWidget::UpdateAvailableAmmo);
		BaseCharacter->OnAvailableAmmoCountChangedUIDelegate.AddUObject(this, &UAmmoWidget::UpdateAvailableAmmoToAdd);
	}
}

void UAmmoWidget::UpdateAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
}

void UAmmoWidget::UpdateAvailableAmmo(int32 NewAvailableAmmo)
{
	AvailableAmmo = NewAvailableAmmo;
}

void UAmmoWidget::UpdateAvailableAmmoToAdd(int32 NewAvailableAmmoToAdd)
{
	AvailableAmmoToAdd = NewAvailableAmmoToAdd;
	OnAvailableAmmoChanged();
}
