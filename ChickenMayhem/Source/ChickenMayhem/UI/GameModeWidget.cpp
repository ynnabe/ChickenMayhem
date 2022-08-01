// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameModeWidget.h"

#include "Gamemodes/BaseGameMode.h"

void UGameModeWidget::StartGame()
{
	ABaseGameMode* GameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	RemoveFromParent();
	GameMode->StartGame();
}
