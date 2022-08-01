// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "ChickenCharacter.h"
#include "ChickenMayhem/AnimInstances/Weapon/WeaponAnimInstance.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Actors/Interactive/AmmoActor.h"
#include "Controllers/BasePlayerController.h"
#include "Gamemodes/BaseGameMode.h"
#include "Kismet/GameplayStatics.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->SetupAttachment(RootComponent);
	
	CharacterAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	CharacterAudioComponent->SetupAttachment(RootComponent);

	FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
	FireAudioComponent->SetupAttachment(WeaponMeshComponent);

	ReloadAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ReloadAudioComponent"));
	ReloadAudioComponent->SetupAttachment(WeaponMeshComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(WeaponMeshComponent);
}

void ABaseCharacter::CalcWeaponMeshNewRotation()
{
	if(bIsGameEnded)
	{
		return;
	}
	
	FVector WorldLocation;
	FVector WorldDirection;
	BasePlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	FRotator NewRotation = WorldDirection.ToOrientationRotator();
	WeaponMeshComponent->SetWorldRotation(FRotator(0.0f, NewRotation.Yaw - 90.0f, -NewRotation.Pitch));
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CalcWeaponMeshNewRotation();
}

int32 ABaseCharacter::GetAmmo() const
{
	return Ammo;
}

int32 ABaseCharacter::GetAvailableAmmo() const
{
	return AvailableAmmo;
}


void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	BasePlayerController = StaticCast<ABasePlayerController*>(GetController());
	BasePlayerController->CurrentMouseCursor = EMouseCursor::Crosshairs;
	WeaponAnimInstance = StaticCast<UWeaponAnimInstance*>(WeaponMeshComponent->GetAnimInstance());
	BaseGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	BaseGameMode->OnGameEndDelegate.AddUObject(this, &ABaseCharacter::GameEnd);
	SetAmmo(MaxAmmo);
	UpdateAmmoUI();
	UpdateAvailableAmmoUI();
}



void ABaseCharacter::Fire()
{
	if(CanFire())
	{
		FHitResult HitResult;
		Ammo--;
		if(OnAmmoCountChangedDelegate.IsBound())
		{
			OnAmmoCountChangedDelegate.Broadcast(Ammo);
		}
		WeaponAnimInstance->PlayFireAnimation();
		PlayFireSound();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlashFX, Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
		bIsFiring = true;
		GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ABaseCharacter::OnShotFinished, GetShotInterval(), false);
		
		if(bool bIsHit = BasePlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult))
		{
			AInteractiveActor* InteractiveActor = Cast<AInteractiveActor>(HitResult.GetActor());
			if(IsValid(InteractiveActor))
			{
				InteractableObject = HitResult.GetActor();
				InteractableObject->Interact(this);
			}
			
			AChickenCharacter* ChickenActor = Cast<AChickenCharacter>(HitResult.GetActor());
			if(IsValid(ChickenActor))
			{
				FDamageEvent DamageEvent;
				ChickenActor->TakeDamage(Damage, DamageEvent, GetController(), this);
			}
		}
	}
}

void ABaseCharacter::UpdateAmmoUI()
{
	if(OnAmmoCountChangedDelegate.IsBound())
	{
		OnAmmoCountChangedDelegate.Broadcast(Ammo);
	}
}

void ABaseCharacter::UpdateAvailableAmmoUI()
{
	if(OnAvailableAmmoCountChangedDelegate.IsBound())
	{
		OnAvailableAmmoCountChangedDelegate.Broadcast(AvailableAmmo);
	}
}

void ABaseCharacter::UpdateAvailableAmmoToAddUI(int32 AvailableAmmoToAdd)
{
	if(OnAvailableAmmoCountChangedUIDelegate.IsBound())
	{
		OnAvailableAmmoCountChangedUIDelegate.Broadcast(AvailableAmmoToAdd);
	}
}

void ABaseCharacter::Reload()
{
	bIsReloading = true;
	float MontageDuration;
	PlayReloadSound();
	WeaponAnimInstance->PlayReloadAnimation(MontageDuration);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ABaseCharacter::EndReload, MontageDuration, false);
}

void ABaseCharacter::GameEnd()
{
	bIsGameEnded = true;
	BasePlayerController->CurrentMouseCursor = EMouseCursor::Default;
	BasePlayerController->SetPause(true);
}

void ABaseCharacter::EndReload()
{
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	int32 CurrentAmmo = GetAmmo();
	int32 AmmoToReload = MaxAmmo - GetAmmo();
	int32 ReloadedAmmo = FMath::Min(AvailableAmmo, AmmoToReload);
	
	AvailableAmmo -= ReloadedAmmo;
	SetAmmo(ReloadedAmmo + CurrentAmmo);
	UpdateAmmoUI();
	UpdateAvailableAmmoUI();
	bIsReloading = false;
}

float ABaseCharacter::GetShotInterval()
{
	return 60.0f / RateOfFire;
}

void ABaseCharacter::OnShotFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
	bIsFiring = false;
	if(Ammo == 0 && AvailableAmmo == 0)
	{
		BaseGameMode->EndGame();
	}
	
	if(Ammo == 0)
	{
		Reload();
	}
}

void ABaseCharacter::SetAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
	UpdateAmmoUI();
}

void ABaseCharacter::AddAvailableAmmo(int32 NewAvailableAmmo)
{
	AvailableAmmo += NewAvailableAmmo;
	UpdateAvailableAmmoUI();
	UpdateAvailableAmmoToAddUI(NewAvailableAmmo);
}

bool ABaseCharacter::CanFire()
{
	bool Result = true;
	if(Ammo == 0)
	{
		Result = false;
	}
	if(bIsReloading)
	{
		Result = false;
	}
	if(bIsFiring)
	{
		Result = false;
	}
	return Result;
}

void ABaseCharacter::PlayFireSound() const
{
	FireAudioComponent->Play();
}

void ABaseCharacter::PlayReloadSound() const
{
	ReloadAudioComponent->Play();
}

void ABaseCharacter::PlayPickUpSound(EPickUpSound Sound)
{
	switch(Sound)
	{
	case EPickUpSound::Ammo:
		{
			CharacterAudioComponent->Sound = AmmoPickUpSound;
			break;
		}
	case EPickUpSound::IncreaseTime:
		{
			CharacterAudioComponent->Sound = IncreaseTimePickUpSound;
			break;
		}
	case EPickUpSound::StartSlowDown:
		{
			CharacterAudioComponent->Sound = StartSlowdownPickUpSound;
			break;
		}
	case EPickUpSound::StopSlowDown:
		{
			CharacterAudioComponent->Sound = StopSlowdownPickUpSound;
			break;
		}
	}
	CharacterAudioComponent->Play();
}

void ABaseCharacter::IncreaseTime(int32 MinutesToAdd, int32 SecondsToAdd)
{
	BaseGameMode->AddTime(MinutesToAdd, SecondsToAdd);
}

void ABaseCharacter::StartSlowDownTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);
	OnSlowDownTime(true);
	PlayPickUpSound(EPickUpSound::StartSlowDown);
	if(OnTimeSlowDown.IsBound())
	{
		OnTimeSlowDown.Execute(true);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerSlowdown, this, &ABaseCharacter::StopSlowDownTime, SlowdownDuration, false);
}

void ABaseCharacter::StopSlowDownTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	OnSlowDownTime(false);
	PlayPickUpSound(EPickUpSound::StopSlowDown);
	if(OnTimeSlowDown.IsBound())
	{
		OnTimeSlowDown.Execute(false);
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

