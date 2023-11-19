// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Plant_Actor.h"


// Sets default values
APlant_Actor::APlant_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = defaultSceneRoot;

	plantMesh = CreateDefaultSubobject<UStaticMeshComponent>("Plant Mesh");
	plantMesh->AttachToComponent(defaultSceneRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//plantMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	WorldSpaceWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorldSpaceWidget"));
	WorldSpaceWidgetComponent->AttachToComponent(defaultSceneRoot, FAttachmentTransformRules::KeepRelativeTransform); // Attach it to the root component, or choose another component to attach it to.


//plantMesh->SetRelativeLocation(RootComponent.location)

	ageComponent = CreateDefaultSubobject<UAgeComponent>("Plant Age");

	waterStat = CreateDefaultSubobject<UNeedStat>("Water Stat");
	needs.Add(waterStat);

	growthTimer = CreateDefaultSubobject<UTimer>("Growth Timer");

	growthTimer->TimerFinished.AddDynamic(this, &APlant_Actor::Grow);;

	plantUIElements = CreateDefaultSubobject<UPlantUIElements>("UIElements");
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
bool APlant_Actor::SetUpUI()
{

	// Create the Widget Component

	if (!WorldSpaceWidgetComponent)
		return false;

	
	if (!WorldSpaceWidgetComponent->GetWidget())
		return false;
	
	UPlantUIWidget* plantUI = Cast<UPlantUIWidget>(WorldSpaceWidgetComponent->GetWidget());
	if (plantUI)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Worked");
		plantUI->SetPlantImage(plantUIElements->GetTexture());
		plantUI->SetPlantDescription(plantUIElements->GetDescription());
	}


	return true;
}
// Called when the game starts or when spawned
void APlant_Actor::BeginPlay()
{
	Super::BeginPlay();

	//when plant is created growth and mesh size should always start at 0
	growth = 0;
	SetPlantSize(growth);

	SetUpUI();

}

// Called every frame
void APlant_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

