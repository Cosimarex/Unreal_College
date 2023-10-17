// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class REVISIONCPP_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
public:

	virtual void OnPossess(APawn* InPawn)override;
    
};

