// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactive/Interface/Interactable.h"
#include "GameFramework/Character.h"
#include "Gamemodes/BaseGameMode.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoCountChanged, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvailableAmmoCountChanged, int32, int32);
DECLARE_DELEGATE_OneParam(FOnTimeSlowDown, bool);

class ABasePlayerController;
class UWeaponAnimInstance;
class UNiagaraSystem;

UENUM()
enum class EPickUpSound
{
	Ammo,
	IncreaseTime,
	StartSlowDown,
	StopSlowDown
};

UCLASS()
class CHICKENMAYHEM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FOnAmmoCountChanged OnAmmoCountChangedDelegate;
	FOnAmmoCountChanged OnAvailableAmmoCountChangedDelegate;
	FOnAmmoCountChanged OnAvailableAmmoCountChangedUIDelegate;
	FOnTimeSlowDown OnTimeSlowDown;
	
	void CalcWeaponMeshNewRotation();
	
	int32 GetAmmo() const;
	
	int32 GetAvailableAmmo() const;

	virtual void Fire();
	
	virtual void Reload();
	
	virtual void SetAmmo(int32 NewAmmo);
	
	virtual void AddAvailableAmmo(int32 NewAvailableAmmo);
	
	void UpdateAmmoUI();

	void UpdateAvailableAmmoUI();

	void UpdateAvailableAmmoToAddUI(int32 AvailableAmmoToAdd);
	
	virtual bool CanFire();

	void PlayFireSound() const;

	void PlayReloadSound() const;

	void PlayPickUpSound(EPickUpSound Sound);

	void IncreaseTime(int32 MinutesToAdd, int32 SecondsToAdd);

	void StartSlowDownTime();

	void StopSlowDownTime();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayMenu(bool bIsPaused);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSlowDownTime(bool State);

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon")
	float Damage = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon", meta=(ClampMin = 0.0, UIMin = 0.0f))
	float RateOfFire = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon", meta=(ClampMin = 0.0, UIMin = 0.0f))
	float RangeOfFire = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon")
	USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon")
	UNiagaraSystem* MuzzleFlashFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UAudioComponent* CharacterAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UAudioComponent* FireAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UAudioComponent* ReloadAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USoundBase* AmmoPickUpSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USoundBase* IncreaseTimePickUpSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USoundBase* StartSlowdownPickUpSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USoundBase* StopSlowdownPickUpSound;
	
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	int32 MaxAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	int32 AvailableAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time")
	float TimeDilation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Time")
	float SlowdownDuration;

private:

	TWeakObjectPtr<ABaseGameMode> BaseGameMode;
	TWeakObjectPtr<ABasePlayerController> BasePlayerController;
	TWeakObjectPtr<UWeaponAnimInstance> WeaponAnimInstance;

	TScriptInterface<IInteractable> InteractableObject;
	
	int32 Ammo;
	FTimerHandle ReloadTimer;
	FTimerHandle ShotTimer;
	bool bIsReloading = false;
	bool bIsFiring = false;
	bool bIsGameEnded = false;

	FTimerHandle TimerSlowdown;

	void GameEnd();

	void EndReload();
	float GetShotInterval();
	void OnShotFinished();
};
