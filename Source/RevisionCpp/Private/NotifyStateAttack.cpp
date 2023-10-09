// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStateAttack.h"


void UNotifyStateAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		HeroCharacter = Cast<AHeroCharacter>(MeshComp->GetOwner());
		if (HeroCharacter)
		{
			HeroCharacter->ActivateRightWeapon();
		}
	}
}

void UNotifyStateAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		HeroCharacter = Cast<AHeroCharacter>(MeshComp->GetOwner());
		if (HeroCharacter)
		{
			HeroCharacter->DeactivateRightWeapon();
		}
	}
}