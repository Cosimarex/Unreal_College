// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAttack::MainAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && MainAttackMontage)
	{
		// get no of montage section
		int32 const SectionCount = MainAttackMontage->CompositeSections.Num();

		FName const SectionName = GetAttackSectionName(SectionCount);
		int32 const SectionIndex = MainAttackMontage->GetSectionIndex(SectionName);
		float const SectionLength= MainAttackMontage->GetSectionLength(SectionIndex);
					
		GetCharacterMovement()->DisableMovement();

		AnimInstance->Montage_Play(MainAttackMontage);
		AnimInstance->Montage_JumpToSection(SectionName, MainAttackMontage);
		GetWorldTimerManager().SetTimer(TimerAttack, this, &AEnemyAttack::ResetMovementWalking, SectionLength);
	}

}

void AEnemyAttack::ResetMovementWalking()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

FName AEnemyAttack::GetAttackSectionName(int SectionCount)
{
	FName SectionName;

	const int32 Section{ FMath::RandRange(1,SectionCount) };

	switch(Section)
	{
	case 1:
		SectionName = FName("MainAttack1");
		break;
	case 2:
		SectionName = FName("MainAttack2");
		break;
	}

	return FName();
}


void AEnemyAttack::MainMeleeAttack()
{
	MainAttack();
}