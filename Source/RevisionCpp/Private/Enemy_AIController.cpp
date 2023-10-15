// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void AEnemy_AIController::BeginPlay()
{
    // Create the Behavior Tree Component and Blackboard Component
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // Set the default Blackboard asset (replace "BlackboardDataAssetPath" with the actual path)
    //static ConstructorHelpers::FObjectFinder<AI_Var> BlackboardDataAsset(TEXT("A:/College/RevisionCpp/Unreal_College/Content/AI/AI_Var.uasset"));
    if (BlackBoardData)
    {
        BlackboardComponent->InitializeBlackboard(*BlackBoardData);
    }

    // Set the default Behavior Tree asset (replace "BehaviorTreeAssetPath" with the actual path)
    //static ConstructorHelpers::FObjectFinder<AI_Behavior_Tree> BehaviorTreeAsset(TEXT("A:/College/RevisionCpp/Unreal_College/Content/AI/AI_Behavior_Tree.uasset"));
    if (BehaviorTree)
    {
        BehaviorTreeComponent->StartTree(*BehaviorTree);
    }
}