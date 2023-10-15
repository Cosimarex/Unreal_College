// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy_AIController.h"

#include "SearchForRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class REVISIONCPP_API USearchForRandomPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USearchForRandomPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
