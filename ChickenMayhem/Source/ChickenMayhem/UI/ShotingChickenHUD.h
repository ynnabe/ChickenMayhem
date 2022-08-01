// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShotingChickenHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API AShotingChickenHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
protected:

	void OnGameEnd();
	
	void AddToScreen(TSubclassOf<UUserWidget> WidgetClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> GameHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UUserWidget> GameEndHUD;

private:

	TWeakObjectPtr<UUserWidget> CurrentActiveWidget;
	
};
