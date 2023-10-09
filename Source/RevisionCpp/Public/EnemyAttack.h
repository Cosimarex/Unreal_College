// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyAttack.generated.h"



class UAnimMontage;
/**
 * 
 */
UCLASS()
class REVISIONCPP_API AEnemyAttack : public AEnemy
{
	GENERATED_BODY()
	

public:

	//AEnemyAttack();

protected:

	void MainAttack();

	void ResetMovementWalking();

	FName GetAttackSectionName(int SectionCount);

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Combat")
	UAnimMontage* MainAttackMontage;

	FTimerHandle TimerAttack;

	UFUNCTION(BlueprintCallable)
	void MainMeleeAttack();
};
