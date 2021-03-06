// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoCountChanged, int32);

class ABasePlayerController;
UCLASS()
class CHICKENMAYHEM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
	void CalcWeaponMeshNewRotation();

	FOnAmmoCountChanged OnAmmoCountChangedDelegate;
	FOnAmmoCountChanged OnAvailableAmmoCountChangedDelegate;

	virtual void Tick(float DeltaSeconds) override;

	int32 GetAmmo() const;
	
	int32 GetAvailableAmmo() const;

	virtual void Fire();
	
	void UpdateAmmoUI();

	virtual void Reload();

	virtual void SetAmmo(int32 NewAmmo);

	virtual bool CanFire();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon")
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon | Properties")
	UCurveFloat* FireAnimationCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment | Weapon | Properties", meta=(MakeEditWidget))
	FVector EndWeaponMeshLocation;
	
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	int32 MaxAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	int32 AvailableAmmo;

private:

	TWeakObjectPtr<ABasePlayerController> BasePlayerController;

	FVector WeaponMeshInitialLocation;
	FTimeline WeaponMeshTimeline;
	UFUNCTION()
	void TickWeaponMeshAnimation(float Value);
	UFUNCTION()
	void OnWeaponMeshEndReached();
	bool bIsFire = false;
	
	int32 Ammo;
};
