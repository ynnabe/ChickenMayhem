// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AmmoWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAvailableAmmoChanged();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	int32 Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	int32 AvailableAmmo;

	UPROPERTY(BlueprintReadOnly)
	int32 AvailableAmmoToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	UTexture* AmmoIcon;

private:

	void UpdateAmmo(int32 NewAmmo);

	void UpdateAvailableAmmo(int32 NewAvailableAmmo);

	void UpdateAvailableAmmoToAdd(int32 NewAvailableAmmoToAdd);
	
};
