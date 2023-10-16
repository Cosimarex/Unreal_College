// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy():

	Health(100.f),
	MaxHealth(100.f)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::MeleeHit_Implementation(FHitResult HitResult)
{
	// play sound

	//give a niagra effect

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f) {

		FString DebugMessage = FString::Printf(TEXT("Enemy Health %f"), Health);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugMessage);
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance && DeathMontage)
		{
			// get no of montage section
			int32 const SectionCount = DeathMontage->CompositeSections.Num();

			FName const SectionName = "";
			int32 const SectionIndex = DeathMontage->GetSectionIndex(SectionName);
			float const SectionLength = DeathMontage->GetSectionLength(SectionIndex);


			AnimInstance->Montage_Play(DeathMontage);
			AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
			GetWorldTimerManager().SetTimer(DeathTimer, this,&AEnemy::DestroySelf, SectionLength);
		}
	}

	else {
		Health -= DamageAmount;
	}
	
	return DamageAmount;

}

void AEnemy::EnemyMainAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called from Enemy Class"));
}

void AEnemy::DestroySelf()
{
	Destroy();
}
