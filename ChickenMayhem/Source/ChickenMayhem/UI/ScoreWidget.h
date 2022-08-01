// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

protected:
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBScore;

private:

	void UpdateScore(int32 NewScore);
	
};
