// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"

#include "Gamemodes/BaseGameMode.h"
#include "Kismet/KismetTextLibrary.h"

void UScoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ABaseGameMode* BaseGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	if(IsValid(BaseGameMode))
	{
		BaseGameMode->OnScoreUpdateDelegate.AddUObject(this, &UScoreWidget::UpdateScore);
	}
}

void UScoreWidget::UpdateScore(int32 NewScore)
{
	TBScore->SetText(UKismetTextLibrary::Conv_IntToText(NewScore, false, false, 5, 324));
}
