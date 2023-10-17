// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatInterface.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Enemy.generated.h"

UCLASS()
class REVISIONCPP_API AEnemy : public ACharacter , public ICombatInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroySelf();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* Tree;

	// Enemy name to display on HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FName EnemyName;

	// Starting damage for enemy character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BaseDamage;

	// Current health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health;

	// Maximum allowed health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth;

	UBehaviorTree* GetBehaviourTree() const;

public:

	// Override melee hit interface
	virtual void MeleeHit_Implementation(FHitResult HitResult) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void EnemyMainAttack();

	FTimerHandle DeathTimer;

	


};
