// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChickenMayhem/Characters/BaseCharacter.h"
#include "ChickenMayhem/UI/AmmoWidget.h"
#include "ChickenMayhem/UI/PlayerHUDWidget.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	virtual void SetPawn(APawn* InPawn) override;

protected:

	virtual void SetupInputComponent() override;

	float CalculateEdgeScroll();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidgetClass;

private:

	TWeakObjectPtr<UPlayerHUDWidget> PlayerHUDWidget;

	void CreateAndInitializeWidgets();

	void TurnRight(float Value);

	void Fire();

	void Reload();

	TWeakObjectPtr<ABaseCharacter> CachedBaseCharacter;
};
