// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HeroInterface.h"
#include "GameFramework/Character.h"
#include "HeroCharacter.generated.h"

UCLASS()
class REVISIONCPP_API AHeroCharacter : public ACharacter , public IHeroInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	// Activate and deactivate weapon boxes
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float BaseDamage=20.0f;

	// Current health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float Health;

	// Maximum allowed health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float MaxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayAnimMontage(UAnimMontage* MontagetoPlay, FName SeciontName = "Default");

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnRate(float Rate);

	void LookUpRate(float Rate);


	void EnableWalk();

	void MainAttack();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	// Right weapon overlap
	UFUNCTION()
	void OnRightWeaponOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	float DefaultTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float DefaultLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage")
	UAnimMontage* MainAttackMontage;

	FTimerHandle TimerMovementWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UBoxComponent* RightWeaponCollision;
};
