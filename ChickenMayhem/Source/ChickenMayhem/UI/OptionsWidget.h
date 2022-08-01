// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "OptionsWidget.generated.h"

UENUM()
enum class EQuality : uint8
{
	Low,
	Medium,
	High,
	Epic,
	Cinematic
};

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;


protected:

	UFUNCTION(BlueprintCallable)
	void ApplySettings();

	UFUNCTION(BlueprintCallable)
	void OnChangeWindowMode();

	UPROPERTY(meta=(BindWidget))
	UComboBoxString* GraphicsQualityComboBox;

	UPROPERTY(meta=(BindWidget))
	UComboBoxString* ResolutionComboBox;

	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowModeComboBox;

	EWindowMode::Type CurrentWindowMode;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Resolutions")
	TArray<FIntPoint> Resolutions;
	
};
