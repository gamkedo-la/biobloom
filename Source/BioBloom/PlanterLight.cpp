// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanterLight.h"


// Sets default values for this component's properties
UPlanterLight::UPlanterLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlanterLight::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlanterLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1234567, 15.f, FColor::Yellow, TEXT("Hello I'm an updated light message that overwrites itself"));
	}
}

