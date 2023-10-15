// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"

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

	AEnemyAttack();
	//Right Weapon
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();

	virtual void ActivateLeftWeapon();
	virtual void DeactivateLeftWeapon();

protected:

	virtual void BeginPlay() override;

	void MainAttack();

	void ResetMovementWalking();

	FName GetAttackSectionName(int SectionCount);

	

	UFUNCTION()
		void OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
    UFUNCTION()
	void OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Combat")
	UAnimMontage* MainAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		UBoxComponent* RightWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		UBoxComponent* LeftWeaponCollision;

	FTimerHandle TimerAttack;

	UFUNCTION(BlueprintCallable)
	void MainMeleeAttack();

	UPawnSensingComponent* SensingComponent;

	void OnSeePawn(APawn* Pawn);
};
