// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Gamemodes/BaseGameMode.h"
#include "GameEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBScore;

private:

	void SetTBScore(int32 Score);

	TWeakObjectPtr<ABaseGameMode> CachedGameMode;
	
};
