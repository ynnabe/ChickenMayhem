// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartSlowDown(bool State);
	
};
