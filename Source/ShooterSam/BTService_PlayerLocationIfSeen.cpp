// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAI.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AShooterSamCharacter* Player = OwnerController->PlayerCharacter;
	UBlackboardComponent* BlackboardComp = OwnerController->BlackboardComp;

	if (OwnerController && Player && BlackboardComp)
	{
		if (OwnerController->LineOfSightTo(Player))
		{
			BlackboardComp->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
			OwnerController->SetFocus(Player);
		}
		else
		{
			BlackboardComp->ClearValue(GetSelectedBlackboardKey());
			OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
