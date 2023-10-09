// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"


void UHeroAnimInstance::UpdateAnimationProperties(float DeltaTime)
{

	if(HeroCharacter == nullptr)
	{
		HeroCharacter = Cast<AHeroCharacter>(TryGetPawnOwner());
	}

	if (HeroCharacter) {

		FVector Velocity = HeroCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		
		
		bIsInAir =HeroCharacter->GetCharacterMovement()->IsFalling();
		 
		FRotator AimRotation = HeroCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(HeroCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

	}

}

void UHeroAnimInstance::NativeInitializeAnimation()
{
	HeroCharacter = Cast<AHeroCharacter>(TryGetPawnOwner());
	
}
