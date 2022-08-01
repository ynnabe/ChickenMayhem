// Fill out your copyright notice in the Description page of Project Settings.


#include "ChickenAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"


void UChickenAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	CachedChickenCharacter = StaticCast<AChickenCharacter*>(TryGetPawnOwner());
}

void UChickenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!CachedChickenCharacter.IsValid())
	{
		return;
	}
	WalkSpeed = CachedChickenCharacter->GetMovementComponent()->Velocity.Size();
}
