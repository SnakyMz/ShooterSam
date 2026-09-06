// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), EnemyCharacters);

	for (AActor* EnemyAI : EnemyCharacters)
	{
		AShooterAI* ShooterAI = Cast<AShooterAI>(EnemyAI);
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(PlayerCharacter);
		}
	}
}