// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AI_Left_Attack.h"

void UEnemy_AI_Left_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyAttack = Cast<AEnemyAttack>(MeshComp->GetOwner());
		if (EnemyAttack)
		{
			EnemyAttack->ActivateLeftWeapon();
		}
	}
}
void UEnemy_AI_Left_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyAttack = Cast<AEnemyAttack>(MeshComp->GetOwner());
		if (EnemyAttack)
		{
			EnemyAttack->DeactivateLeftWeapon();
		}
	}
}
