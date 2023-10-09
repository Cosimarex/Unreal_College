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

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Died"));

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

