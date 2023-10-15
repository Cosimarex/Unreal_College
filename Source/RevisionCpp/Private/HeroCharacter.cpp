// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "CombatInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "kismet/GameplayStatics.h"


// Sets default values
AHeroCharacter::AHeroCharacter():

	DefaultTurnRate(45.f),
	DefaultLookUpRate(45.f)


{


	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setup pitch and roill

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	//rotate only in yaw 

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);


	//Jump
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.1f;

	// Right weapon collision box
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Box"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));

	

}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//binding dynamically overlap to collisionbox
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AHeroCharacter::OnRightWeaponOverlap);

	// Setup right weapon collision box
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void AHeroCharacter::MoveForward(float Value) {


	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };

		AddMovementInput(Direction, Value);

	}

}


void AHeroCharacter::MoveRight(float Value) {


	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction, Value);

		}

}

void AHeroCharacter::TurnRate(float Rate) {

	//turning per delta seconds
	AddControllerYawInput(Rate * DefaultTurnRate * GetWorld()->GetDeltaSeconds());


}

void AHeroCharacter::LookUpRate(float Rate) {

	//turning per delta seconds
	AddControllerPitchInput(Rate * DefaultLookUpRate * GetWorld()->GetDeltaSeconds());


}



void AHeroCharacter::EnableWalk()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AHeroCharacter::MainAttack()
{
	PlayAnimMontage(MainAttackMontage, FName("MainAttack"));
}

void AHeroCharacter::PlayAnimMontage(UAnimMontage* MontagetoPlay,FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if(AnimInstance && MontagetoPlay)
	{
		if(!AnimInstance->Montage_IsPlaying(MontagetoPlay))
		{
			GetCharacterMovement()->DisableMovement();

			int32 const SectionIndex = MontagetoPlay->GetSectionIndex(SectionName);
			int32 const SectionLength = MontagetoPlay->GetSectionLength(SectionIndex);

			AnimInstance->Montage_Play(MontagetoPlay);
			AnimInstance->Montage_JumpToSection(SectionName);

			GetWorldTimerManager().SetTimer(TimerMovementWalking, this, &AHeroCharacter::EnableWalk, SectionLength);
		}
	}
}


void AHeroCharacter::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Apply damage"));

	if (IsValid(SweepResult.GetActor())) {

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(SweepResult.GetActor());

		if (CombatInterface) {

			//does implementation store the value
			CombatInterface->MeleeHit_Implementation(SweepResult);
		}
	}


	float BaseDamage = 20.f;
	// Apply damage to enemy
	UGameplayStatics::ApplyDamage(
		SweepResult.GetActor(),
		BaseDamage,
		GetController(),
		this,
		UDamageType::StaticClass());
	
}


void AHeroCharacter::ActivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Activate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


void AHeroCharacter::DeactivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Deactivate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent)

		//PlayerMove

		PlayerInputComponent->BindAxis("MoveForward", this, &AHeroCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);
		PlayerInputComponent->BindAxis("TurnRate", this, &AHeroCharacter::TurnRate);
		PlayerInputComponent->BindAxis("LookUpRate", this, &AHeroCharacter::LookUpRate);
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("Look", this, &APawn::AddControllerPitchInput);
		

		//Action Binding

		PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

		//Main Attack
		PlayerInputComponent->BindAction("MainAttack", IE_Pressed, this, &AHeroCharacter::MainAttack);

}