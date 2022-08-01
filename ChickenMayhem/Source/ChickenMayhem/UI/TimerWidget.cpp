// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TimerWidget.h"

#include "Gamemodes/BaseGameMode.h"
#include "Kismet/KismetTextLibrary.h"

void UTimerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ABaseGameMode* BaseGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	if(IsValid(BaseGameMode))
	{
		BaseGameMode->OnMinutesUpdateDelegate.AddUObject(this, &UTimerWidget::UpdateMinutes);
		BaseGameMode->OnSecondsUpdateDelegate.AddUObject(this, &UTimerWidget::UpdateSeconds);
		BaseGameMode->UpdateTimeToAddDelegate.AddUObject(this, &UTimerWidget::UpdateTimeToAdd);
		BaseGameMode->OnGameEndingDelegate.AddUObject(this, &UTimerWidget::OnGameEnding);
	}
}

void UTimerWidget::UpdateTimeToAdd(int32 MinutesToAdd, int32 SecondsToAdd)
{
	TBTimeMinutesToAdd->SetText(UKismetTextLibrary::Conv_IntToText(MinutesToAdd, false, true, 2, 2));
	TBTimeSecondsToAdd->SetText(UKismetTextLibrary::Conv_IntToText(SecondsToAdd, false, true, 2, 2));
	OnTimeIncrease();
}

void UTimerWidget::UpdateMinutes(int32 NewMinutes)
{
	TBMinutes->SetText(UKismetTextLibrary::Conv_IntToText(NewMinutes, false, true, 2, 2));
}

void UTimerWidget::UpdateSeconds(int32 NewSeconds)
{
	TBSeconds->SetText(UKismetTextLibrary::Conv_IntToText(NewSeconds, false, true, 2, 2));
}
