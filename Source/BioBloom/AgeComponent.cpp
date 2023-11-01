// Fill out your copyright notice in the Description page of Project Settings.


#include "AgeComponent.h"

// Sets default values for this component's properties
UAgeComponent::UAgeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ageTimer = CreateDefaultSubobject<UTimer>("AgeTimer");
	ageTimer->TimerFinished.AddDynamic(this, &UAgeComponent::Age);
	// ...
}


void UAgeComponent::Age()
{
	currentAge++;
}

// Called when the game starts
void UAgeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

