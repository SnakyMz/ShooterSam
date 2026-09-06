// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(SceneComponent);

	MuzzleFlash = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlash->SetupAttachment(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	MuzzleFlash->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	MuzzleFlash->Activate(true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), MuzzleSound, GetActorLocation());

	if (OwnerController)
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
		FVector EndLocation = ViewPointLocation + (ViewPointRotation.Vector() * MaxRange);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		if (GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

