// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Controllers/BasePlayerController.h"
#include "Kismet/KismetMathLibrary.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->SetupAttachment(RootComponent);
}

void ABaseCharacter::CalcWeaponMeshNewRotation()
{
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
	WeaponMeshInitialLocation = WeaponMeshComponent->GetComponentLocation();
	SetAmmo(MaxAmmo);
	UpdateAmmoUI();
	if(IsValid(FireAnimationCurve))
	{
		FOnTimelineFloatStatic OnTimelineUpdate;
		OnTimelineUpdate.BindUFunction(this, FName("TickWeaponMeshAnimation"));
		WeaponMeshTimeline.AddInterpFloat(FireAnimationCurve, OnTimelineUpdate);

		FOnTimelineEventStatic OnTimelineFinished;
		OnTimelineFinished.BindUFunction(this, FName("OnWeaponMeshEndReached"));
		WeaponMeshTimeline.SetTimelineFinishedFunc(OnTimelineFinished);
	}
}

void ABaseCharacter::TickWeaponMeshAnimation(float Value)
{
	FVector NewLocation = FMath::Lerp(WeaponMeshInitialLocation, EndWeaponMeshLocation, Value);
	WeaponMeshComponent->SetRelativeLocation(NewLocation);
}

void ABaseCharacter::OnWeaponMeshEndReached()
{
	if(bIsFire)
	{
		WeaponMeshTimeline.Reverse();
		bIsFire = false;
	}
}


void ABaseCharacter::Fire()
{
	if(CanFire())
	{
		FHitResult HitResult;
		if(bool bIsHit = BasePlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult))
		{
			Ammo--;
			if(OnAmmoCountChangedDelegate.IsBound())
			{
				OnAmmoCountChangedDelegate.Broadcast(Ammo);
			}
			if(Ammo == 0)
			{
				Reload();
			}
			WeaponMeshTimeline.Play();
			bIsFire = true;
		}
	}
}

void ABaseCharacter::UpdateAmmoUI()
{
	if(OnAvailableAmmoCountChangedDelegate.IsBound())
	{
		OnAvailableAmmoCountChangedDelegate.Broadcast(AvailableAmmo);
	}
	if(OnAmmoCountChangedDelegate.IsBound())
	{
		OnAmmoCountChangedDelegate.Broadcast(Ammo);
	}
}

void ABaseCharacter::Reload()
{
	int32 CurrentAmmo = GetAmmo();
	int32 AmmoToReload = MaxAmmo - GetAmmo();
	int32 ReloadedAmmo = FMath::Min(AvailableAmmo, AmmoToReload);
	
	AvailableAmmo -= ReloadedAmmo;
	SetAmmo(ReloadedAmmo + CurrentAmmo);
	UpdateAmmoUI();
}

void ABaseCharacter::SetAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
}

bool ABaseCharacter::CanFire()
{
	bool Result = true;
	if(Ammo == 0)
	{
		Result = false;
	}
	return Result;
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

