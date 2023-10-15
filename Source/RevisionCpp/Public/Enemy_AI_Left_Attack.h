// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttack.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "Enemy_AI_Left_Attack.generated.h"

/**
 * 
 */
UCLASS()
class REVISIONCPP_API UEnemy_AI_Left_Attack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY()
		AEnemyAttack* EnemyAttack;


	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
