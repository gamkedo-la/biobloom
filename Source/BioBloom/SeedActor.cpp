// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedActor.h"

// Sets default values
ASeedActor::ASeedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = defaultSceneRoot;

	seedMesh = CreateDefaultSubobject<UStaticMeshComponent>("Seed Mesh");
	seedMesh->AttachToComponent(defaultSceneRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void ASeedActor::GrowSeed()
{
	seedMesh->SetRelativeScale3D(FVector(1));
}

// Called when the game starts or when spawned
void ASeedActor::BeginPlay()
{
	Super::BeginPlay();

	seedMesh->SetRelativeScale3D(FVector(0));
	
}

// Called every frame
void ASeedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

