// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ABaseCharacter;
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class CHICKENMAYHEM_API IInteractable
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE(FOnInteraction);

	virtual void Interact(ABaseCharacter* Character) PURE_VIRTUAL(IInteractable::Interact);
	
};
