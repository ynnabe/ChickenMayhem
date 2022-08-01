// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"

ABaseGameMode::ABaseGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

int32 ABaseGameMode::GetScore() const
{
	return Score;
}

void ABaseGameMode::AddScore(int32 Score_in)
{
	Score += Score_in;
	if(OnScoreUpdateDelegate.IsBound())
	{
		OnScoreUpdateDelegate.Broadcast(Score);
	}
}

void ABaseGameMode::UpdateUIMinutes()
{
	OnMinutesUpdateDelegate.Broadcast(Minutes);
}

void ABaseGameMode::RestartTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseGameMode::OnSecondsEnd, Seconds, false);
}

void ABaseGameMode::UpdateUITimeToAdd(int32 MinutesToAdd, int32 SecondsToAdd)
{
	if(UpdateTimeToAddDelegate.IsBound())
	{
		UpdateTimeToAddDelegate.Broadcast(MinutesToAdd, SecondsToAdd);
	}
	if(OnTimeIncreaseDelegate.IsBound())
	{
		OnTimeIncreaseDelegate.Broadcast();
	}
}

void ABaseGameMode::AddTime(int32 MinutesToAdd, int32 SecondsToAdd)
{
	Seconds = GetWorld()->GetTimerManager().GetTimerRemaining(Timer);
	if(SecondsToAdd + Seconds > 60)
	{
		Minutes++;
		int32 SecondsTemp = (SecondsToAdd + Seconds) - 60;
		Seconds = SecondsTemp;
	}
	else
	{
		Seconds += SecondsToAdd;
	}
	Minutes += MinutesToAdd;
	
	RestartTimer();
	UpdateUIMinutes();
	UpdateUITimeToAdd(MinutesToAdd, SecondsToAdd);
}

bool ABaseGameMode::GetGameEnding() const
{
	return bIsGameEnding;
}

void ABaseGameMode::UpdateUITimerGameEnd()
{
	if(GetWorld()->GetTimerManager().GetTimerRemaining(Timer) <= 10.0f && Minutes == 0)
	{
		if(OnGameEndingDelegate.IsBound() && !bIsGameEnding)
		{
			bIsGameEnding = true;
			OnGameEndingDelegate.Broadcast(bIsGameEnding);
		}
	}
	else
	{
		if(OnGameEndingDelegate.IsBound() && bIsGameEnding)
		{
			bIsGameEnding = false;
			OnGameEndingDelegate.Broadcast(bIsGameEnding);
		}
	}
}

void ABaseGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	OnSecondsUpdateDelegate.Broadcast(GetWorld()->GetTimerManager().GetTimerRemaining(Timer));
	UpdateUITimerGameEnd();
}

void ABaseGameMode::UpdateUISeconds()
{
	OnSecondsUpdateDelegate.Broadcast(Seconds);
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameMode::StartGame()
{
	Minutes = StartMinutes;
	Seconds = StartSeconds;
	UpdateUIMinutes();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseGameMode::OnSecondsEnd, Seconds, false);
	if(OnGameStart.IsBound())
	{
		OnGameStart.Broadcast();
	}
}

void ABaseGameMode::EndGame()
{
	OnGameEndDelegate.Broadcast();
	OnGameEndWidgetViewDelegate.Broadcast(Score);
}

void ABaseGameMode::OnSecondsEnd()
{
	if(Minutes == 0)
	{
		EndGame();
	}
	else
	{
		Minutes--;
		UpdateUIMinutes();
		Seconds = 59;
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABaseGameMode::OnSecondsEnd, Seconds, false);
	}
}
