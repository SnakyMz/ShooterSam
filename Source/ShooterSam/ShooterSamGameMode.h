// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterSamCharacter.h"
#include "ShooterSamGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AShooterSamGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	
	/** Constructor */
	AShooterSamGameMode();

	AShooterSamCharacter* PlayerCharacter;
	TArray<AActor*> EnemyCharacters;
};



