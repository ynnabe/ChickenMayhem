// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShotingChickenHUD.h"
#include "PlayerHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Gamemodes/BaseGameMode.h"

void AShotingChickenHUD::BeginPlay()
{
	Super::BeginPlay();

	AddToScreen(GameHUD);

	ABaseGameMode* BaseGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	if(IsValid(BaseGameMode))
	{
		BaseGameMode->OnGameEndDelegate.AddUObject(this, &AShotingChickenHUD::OnGameEnd);
	}
}

void AShotingChickenHUD::OnGameEnd()
{
	AddToScreen(GameEndHUD);
}

void AShotingChickenHUD::AddToScreen(TSubclassOf<UUserWidget> WidgetClass)
{
	if(CurrentActiveWidget.IsValid())
	{
		CurrentActiveWidget->RemoveFromParent();
	}
	if(IsValid(WidgetClass))
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();
		CurrentActiveWidget = Widget;
	}
}

