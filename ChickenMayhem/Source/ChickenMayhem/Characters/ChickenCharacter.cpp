
#include "ChickenCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "../Components/ActorComponents/PatrollingComponent.h"
#include "Components/AudioComponent.h"
#include "Gamemodes/BaseGameMode.h"
#include "Kismet/KismetMathLibrary.h"

AChickenCharacter::AChickenCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	PatrollingComponent = CreateDefaultSubobject<UPatrollingComponent>(TEXT("PatrollingComponent"));

	LootTableComponent = CreateDefaultSubobject<ULootTableComponent>(TEXT("LootTableComponent"));
	
}

void AChickenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBehaviorTree* AChickenCharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}

UPatrollingComponent* AChickenCharacter::GetPatrollingComponent() const
{
	return PatrollingComponent;
}

void AChickenCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	OnTakeAnyDamage.AddDynamic(this, &AChickenCharacter::OnTakeDamage);
}

void AChickenCharacter::SelectRandomDeathSound()
{
	const int32 ArrayIndex = FMath::RandRange(0, DeathSounds.Num() - 1);
	AudioComponent->Sound = DeathSounds[ArrayIndex];
}

TSubclassOf<AInteractiveActor> AChickenCharacter::SelectRandomItem()
{
	LootTableComponent->TotalValue = LootTableComponent->CalculateSum();
	TSubclassOf<AInteractiveActor> Result = LootTableComponent->ChooseLoot();
	return Result;
}


void AChickenCharacter::OnHealthChanged(AActor* DamageCauser)
{
	if(Health == 0.0f)
	{
		Death(DamageCauser);
	}
}

void AChickenCharacter::Death(AActor* DamageCauser)
{
	SelectRandomDeathSound();
	AudioComponent->Play();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathVFX, GetActorLocation(), GetActorRotation());
	GetMesh()->SetVisibility(false);
	
	ABaseGameMode* BaseGameMode = StaticCast<ABaseGameMode*>(GetWorld()->GetAuthGameMode());
	BaseGameMode->AddScore(ScoreCost);

	TSubclassOf<AInteractiveActor> InteractiveActor = SelectRandomItem();
	if(IsValid(InteractiveActor))
	{
		FRotator ToPlayerRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DamageCauser->GetActorLocation());
		GetWorld()->SpawnActor<AInteractiveActor>(InteractiveActor, GetActorLocation(), ToPlayerRotator);
	}
	
	GetWorld()->GetTimerManager().SetTimer(DeathTimer,this, &AChickenCharacter::OnDeath, 5.0f, false);
}

void AChickenCharacter::OnDeath()
{
	Destroy();
}

bool AChickenCharacter::IsAlive()
{
	return Health != 0.0f;
}

void AChickenCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                        AController* InstigatedBy, AActor* DamageCauser)
{
	if(!IsAlive())
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged(DamageCauser);
}
