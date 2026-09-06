// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

}


void AShooterAI::StartBehaviorTree(AShooterSamCharacter* Player)
{
	if (EnemyBehaviorTree)
	{
		ControllerCharacter = Cast<AShooterSamCharacter>(GetPawn());

		if (Player)
		{
			PlayerCharacter = Player;
		}

		RunBehaviorTree(EnemyBehaviorTree);

		BlackboardComp = GetBlackboardComponent();

		if (BlackboardComp && ControllerCharacter && PlayerCharacter)
		{
			BlackboardComp->SetValueAsVector("StartLocation", ControllerCharacter->GetActorLocation());
			BlackboardComp->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
		}
	}
}
