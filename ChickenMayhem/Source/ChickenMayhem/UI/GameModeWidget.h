// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UGameModeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	void StartGame();
	
};
