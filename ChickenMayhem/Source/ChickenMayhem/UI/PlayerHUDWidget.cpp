// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

#include "Characters/BaseCharacter.h"

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ABaseCharacter* Player = StaticCast<ABaseCharacter*>(GetOwningPlayerPawn());
	if(IsValid(Player))
	{
		Player->OnTimeSlowDown.BindUObject(this, &UPlayerHUDWidget::OnStartSlowDown);
	}
}
