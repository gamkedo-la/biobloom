// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantUIElements.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/UMG.h"
// Sets default values for this component's properties
UPlantUIElements::UPlantUIElements()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlantUIElements::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UTexture2D* UPlantUIElements::GetTexture()
{
	return MyTexture;
}


// Called every frame
void UPlantUIElements::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

