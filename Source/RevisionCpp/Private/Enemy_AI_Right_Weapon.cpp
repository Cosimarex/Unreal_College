// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AI_Right_Weapon.h"

void UEnemy_AI_Right_Weapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyAttack = Cast<AEnemyAttack>(MeshComp->GetOwner());
		if (EnemyAttack)
		{
			EnemyAttack->ActivateRightWeapon();
		}
	}
}
void UEnemy_AI_Right_Weapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyAttack = Cast<AEnemyAttack>(MeshComp->GetOwner());
		if (EnemyAttack)
		{
			EnemyAttack->DeactivateRightWeapon();
		}
	}
}
