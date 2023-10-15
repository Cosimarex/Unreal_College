// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchForRandomPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_AIController.h"
#include "EnemyAttack.h"

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
        UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
        FVector Origin = ControlledPawn->GetActorLocation();
        float Radius = 2000.0f;
        FNavLocation RandomNavLocation;
        if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomNavLocation))
        {
            FVector RandomPoint = RandomNavLocation.Location;
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, RandomPoint.ToString());
            
            //AEnemyAttack* OwnerActor = Cast<AEnemyAttack>(GetOwner());
            if (ControlledPawn)
            {
                AAIController* AIController = Cast<AAIController>(ControlledPawn->GetInstigatorController());
                if (AIController)
                {
                    UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
                    // Now you have the blackboard component
                    BlackboardComp->SetValueAsVector("Move to Location", RandomPoint);
                }
            }

            // Now RandomPoint contains a random point on the nav mesh within the specified radius of the origin
        }
        // You now have a reference to the controlled pawn
        // Use ControlledPawn to perform your task actions
    }
    return EBTNodeResult::Succeeded;
}