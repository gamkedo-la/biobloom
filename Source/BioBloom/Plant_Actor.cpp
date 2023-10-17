// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant_Actor.h"


// Sets default values
APlant_Actor::APlant_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	plantMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlantMesh");
	plantMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	waterStat = CreateDefaultSubobject<UNeedStat>("WaterStat");
	needs.Add(waterStat);
	waterStatTimer = CreateDefaultSubobject<UTimer>("WaterStatTimer");
	growthTimer = CreateDefaultSubobject<UTimer>("GrowTimer");

	growthTimer->TimerFinished.AddDynamic(this, &APlant_Actor::Grow);;
}
//This function should hadle growing the plant
void APlant_Actor::Grow()
{
	//check if the there is enough resources in the need stat to grow
	for each (UNeedStat* need in needs)
	{
		if (need->currentStat == 0)
		{
			return;
		}
	}
	growth += growRate;

	if (growth > 1)
		growth = 1;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(growth));

	SetPlantSize(growth);
}
void APlant_Actor::SetPlantSize(const float size)
{
	FVector fullSize = FVector(size);
	plantMesh->SetWorldScale3D(fullSize);
}
// Called when the game starts or when spawned
void APlant_Actor::BeginPlay()
{
	Super::BeginPlay();

	//when plant is created growth and mesh size should always start at 0
	growth = 0;
	SetPlantSize(growth);
	
}

// Called every frame
void APlant_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

