// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class REVISIONCPP_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
public:
    AEnemy_AIController();

    virtual void BeginPlay()override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
        UBehaviorTree* BehaviorTree;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
        UBlackboardData* BlackBoardData;

protected:
    // Declare the Behavior Tree Component and Blackboard Component as class members.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
        class UBehaviorTreeComponent* BehaviorTreeComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
        class UBlackboardComponent* BlackboardComponent;
};

