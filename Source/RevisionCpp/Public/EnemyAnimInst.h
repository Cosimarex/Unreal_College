// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enemy.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInst.generated.h"


class AEnemy;
/**
 * 
 */
UCLASS()
class REVISIONCPP_API UEnemyAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	// This will act like the tick function
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	// Get Enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEnemy* Enemy;

	// Speed of enemy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;

	// Offset yaw used for strafing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementOffsetYaw;
};

