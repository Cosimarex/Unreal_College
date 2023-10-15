// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchForRandomPoint.h"

USearchForRandomPoint::USearchForRandomPoint()
{
	NodeName = "Search For Random Point";
}

EBTNodeResult::Type USearchForRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Your task logic here
    APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

    if (ControlledPawn)
    {
        ControlledPawn->GetTransform().GetLocation();
        
        // You now have a reference to the controlled pawn
        // Use ControlledPawn to perform your task actions
    }
    return EBTNodeResult::Succeeded;
}