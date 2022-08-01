// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TimerWidget.generated.h"



/**
 * 
 */
UCLASS()
class CHICKENMAYHEM_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTimeIncrease();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameEnding(bool bIsGameEnding);

	void UpdateTimeToAdd(int32 MinutesToAdd, int32 SecondsToAdd);

protected:

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBMinutes;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBSeconds;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBTimeMinutesToAdd;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TBTimeSecondsToAdd;


private:

	void UpdateMinutes(int32 NewMinutes);
	void UpdateSeconds(int32 NewSeconds);

};
