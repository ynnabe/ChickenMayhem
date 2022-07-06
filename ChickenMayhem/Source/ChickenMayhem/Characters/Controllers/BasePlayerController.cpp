// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
}

void ABasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<ABaseCharacter>(InPawn);
	CreateAndInitializeWidgets();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("TurnRight", this, &ABasePlayerController::TurnRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayerController::Fire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &ABasePlayerController::Reload);
}

float ABasePlayerController::CalculateEdgeScroll()
{
	float Value = 0.0f;
	
	int32 SizeX;
	int32 SizeY;
	
	float MousePositionX;
	float MousePositionY;
	
	GetViewportSize(SizeX, SizeY);
	GetMousePosition(MousePositionX, MousePositionY);

	float Delta = MousePositionX / SizeX;
	if(Delta >= 0.875)
	{
		Value = 1.0f;
	}
	if(Delta <= 0.125)
	{
		Value = -1.0f;
	}

	return Value;
}

void ABasePlayerController::CreateAndInitializeWidgets()
{
	if(!PlayerHUDWidget.IsValid())
	{
		PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass);
		if(PlayerHUDWidget.IsValid())
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}

void ABasePlayerController::TurnRight(float Value)
{
	AddYawInput(CalculateEdgeScroll());
}

void ABasePlayerController::Fire()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Fire();
	}
}

void ABasePlayerController::Reload()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Reload();
	}
}
