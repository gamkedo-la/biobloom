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

	growthTimer = CreateDefaultSubobject<UTimer>("GrowTimer");

	growthTimer->TimerFinished.AddDynamic(this, &APlant_Actor::Grow);;
}
//this section will control functions related to health
#pragma region Health
float APlant_Actor::GetHealth()
{
	return PlantHealth;
}
void APlant_Actor::SetHealth(float Health)
{
	PlantHealth = Health;

	if (PlantHealth <= 0)
		Die();
}
bool APlant_Actor::Die()
{
	bool hasDied = false;

	Destroy();
	hasDied = true;

	return hasDied;
}

#pragma endregion

//This function should hadle growing the plant
void APlant_Actor::Grow()
{
	//check if the there is enough resources in the need stat to grow
	for (int32 Index = 0; Index < needs.Num(); Index++)
	{
		UNeedStat* need = needs[Index];
		if (need->currentStat == 0)
		{
			//plant will dgrade if not enough resources
			SetHealth(PlantHealth -= DegradationAmount);
			return;
		}

		need->TakeNeed();
	}
	growth += growRate;

	if (growth > 1)
		growth = 1;

	SetPlantSize(growth);

	PlantGrewEvent();
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

