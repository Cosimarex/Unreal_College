// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemy_AIController::AEnemy_AIController()
{
    //BehaviorComp = NewObject<UBehaviorTreeComponent>(this);
    BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    if (BehaviorTree)
    {
        BehaviorComp->StartTree(*BehaviorTree);
    }
}