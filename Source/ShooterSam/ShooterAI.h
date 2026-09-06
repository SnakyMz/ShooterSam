// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterSamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAM_API AShooterAI : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviorTree;

	AShooterSamCharacter* PlayerCharacter;
	AShooterSamCharacter* ControllerCharacter;
	UBlackboardComponent* BlackboardComp;

	void StartBehaviorTree(AShooterSamCharacter* Player);
};
