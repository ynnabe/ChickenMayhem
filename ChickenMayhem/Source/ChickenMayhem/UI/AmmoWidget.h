// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	int32 Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	int32 AvailableAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	UTexture* AmmoIcon;

private:

	void UpdateAmmo(int32 NewAmmo);

	void UpdateAvailableAmmo(int32 NewAvailableAmmo);
	
};
