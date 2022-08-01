// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactive/InteractiveActor.h"

#include "Characters/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AInteractiveActor::AInteractiveActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractiveActor::Interact(ABaseCharacter* Character)
{
	CachedBaseCharacter = Character;
	TimelineUp.Play();
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(MovingCurveUp) && IsValid(MovingCurveToPlayer))
	{
		FOnTimelineFloatStatic OnTimelineUpdate;
		OnTimelineUpdate.BindUFunction(this, FName("MoveUp"));
		TimelineUp.AddInterpFloat(MovingCurveUp, OnTimelineUpdate);

		FOnTimelineEventStatic OnTimelineFinished;
		OnTimelineFinished.BindUFunction(this, FName("MoveUpFinished"));
		TimelineUp.SetTimelineFinishedFunc(OnTimelineFinished);
		FinishedUpLoc = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Height);
	}
}

void AInteractiveActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TimelineUp.TickTimeline(DeltaSeconds);
	TimelineToPlayer.TickTimeline(DeltaSeconds);
}

ABaseCharacter* AInteractiveActor::GetBaseCharacter() const
{
	return CachedBaseCharacter.Get();
}

void AInteractiveActor::MoveUp(float Value)
{
	const FRotator RotatorToPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CachedBaseCharacter->GetActorLocation());
	const FRotator NewRotator = FMath::Lerp(GetActorRotation(), RotatorToPlayer, Value);
	SetActorRotation(NewRotator);
	const FVector NewLoc = FMath::Lerp(GetActorLocation(), FinishedUpLoc, Value);
	SetActorLocation(NewLoc);
}

void AInteractiveActor::MoveUpFinished()
{
	TimelineUp.Stop();
	FOnTimelineFloat OnMoveToPlayerUpdate;
	OnMoveToPlayerUpdate.BindUFunction(this, FName("MoveToPlayer"));
	TimelineToPlayer.AddInterpFloat(MovingCurveToPlayer, OnMoveToPlayerUpdate);

	FOnTimelineEventStatic OnMoveToPlayerFinished;
	OnMoveToPlayerFinished.BindUFunction(this, FName("InteractFinished"));
	TimelineToPlayer.SetTimelineFinishedFunc(OnMoveToPlayerFinished);
	TimelineToPlayer.PlayFromStart();
}

void AInteractiveActor::MoveToPlayer(float Value)
{
	FVector NewLoc = FMath::Lerp(GetActorLocation(), CachedBaseCharacter->GetActorLocation(), Value);
	SetActorLocation(NewLoc);
}

void AInteractiveActor::InteractFinished()
{
	
}

