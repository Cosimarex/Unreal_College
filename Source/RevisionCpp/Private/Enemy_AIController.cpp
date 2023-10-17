// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(AEnemy* const npc=Cast<AEnemy>(InPawn) )
	{
		if (UBehaviorTree* const tree = npc->GetBehaviourTree()) 
		{
			UBlackboardComponent* b;
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}