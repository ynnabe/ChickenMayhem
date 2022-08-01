// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameEnd);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdate, int32);
DECLARE_MULTICAST_DELEGATE(FDelegateOneParam);
DECLARE_MULTICAST_DELEGATE_TwoParams(FUpdateTimeToAdd, int32, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameEnding, bool);


UCLASS()
class CHICKENMAYHEM_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	FOnGameEnd OnGameEndDelegate;
	FOnUpdate OnMinutesUpdateDelegate;
	FOnUpdate OnSecondsUpdateDelegate;
	FOnUpdate OnScoreUpdateDelegate;
	FOnUpdate OnGameEndWidgetViewDelegate;
	FDelegateOneParam OnTimeIncreaseDelegate;
	FDelegateOneParam OnGameStart;
	FOnGameEnding OnGameEndingDelegate;
	FUpdateTimeToAdd UpdateTimeToAddDelegate;

	int32 GetScore() const;
	void AddScore(int32 Score_in);
	void UpdateUIMinutes();
	void RestartTimer();
	void UpdateUITimeToAdd(int32 MinutesToAdd, int32 SecondsToAdd);
	void AddTime(int32 MinutesToAdd, int32 SecondsToAdd);
	bool GetGameEnding() const;
	void UpdateUITimerGameEnd();

	void StartGame();
	void EndGame();
	
protected:

	virtual void Tick(float DeltaSeconds) override;
	void UpdateUISeconds();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Start parameters", meta=(ClampMin=0, UIMin=0))
	int32 StartMinutes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Start parameters", meta=(ClampMin=0, UIMin=0, ClampMax=59, UIMax=59));
	int32 StartSeconds;

private:

	void OnSecondsEnd();

	bool bIsGameEnding = false;

	int32 Minutes;
	int32 Seconds;

	int32 Score;

	FTimerHandle Timer;
	
};
