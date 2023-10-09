// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeroCharacter.h"
#include "HeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class REVISIONCPP_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Movement")
	AHeroCharacter* HeroCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;


};
