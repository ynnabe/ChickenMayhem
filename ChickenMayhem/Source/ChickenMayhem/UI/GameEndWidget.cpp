// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameEndWidget.h"

#include "Gamemodes/BaseGameMode.h"
#include "Kismet/KismetTextLibrary.h"

void UGameEndWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CachedGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	if(CachedGameMode.IsValid())
	{
		CachedGameMode->OnGameEndWidgetViewDelegate.AddUObject(this, &UGameEndWidget::SetTBScore);
	}
}

void UGameEndWidget::SetTBScore(int32 Score)
{
	TBScore->SetText(UKismetTextLibrary::Conv_IntToText(Score, false, false, 5, 324));
}
