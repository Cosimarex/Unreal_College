// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"
#include "CombatInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "kismet/GameplayStatics.h"

AEnemyAttack::AEnemyAttack()
{
	//UPawnSensingComponent* SensingComponent = this->FindComponentByClass<UPawnSensingComponent>();
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
	//SensingComponent->OnSeePawn.AddDynamic(this, &AEnemyAttack::OnSeePawn);

	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Collision"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("weapon_r"));

	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Weapon Collision"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("weapon_l"));
}

void AEnemyAttack::BeginPlay()
{
	Super::BeginPlay();

	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAttack::OnRightWeaponOverlap);

	// Setup right weapon collision box
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAttack::OnLeftWeaponOverlap);

	// Setup right weapon collision box
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

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

void AEnemyAttack::OnSeePawn(APawn* Pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("This is a warning message."));
}

void AEnemyAttack::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Apply damage for Right Weapon"));

	if (IsValid(SweepResult.GetActor())) {

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(SweepResult.GetActor());

		if (CombatInterface) {

			//does implementation store the value
			CombatInterface->MeleeHit_Implementation(SweepResult);
		}
	}


	BaseDamage = 20.f;
	// Apply damage to enemy
	UGameplayStatics::ApplyDamage(SweepResult.GetActor(),BaseDamage,GetController(),this,UDamageType::StaticClass());

}
void AEnemyAttack::OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Apply damage from Left Weapon"));

	if (IsValid(SweepResult.GetActor())) {

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(SweepResult.GetActor());

		if (CombatInterface) {

			//does implementation store the value
			CombatInterface->MeleeHit_Implementation(SweepResult);
		}
	}


	BaseDamage = 20.f;
	// Apply damage to enemy
	UGameplayStatics::ApplyDamage(SweepResult.GetActor(),BaseDamage,GetController(),this,UDamageType::StaticClass());

}

void AEnemyAttack::ActivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Activate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


void AEnemyAttack::DeactivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Deactivate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyAttack::ActivateLeftWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Activate weapon"));
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


void AEnemyAttack::DeactivateLeftWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Deactivate weapon"));
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}