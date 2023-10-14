// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant_Actor.h"


// Sets default values
APlant_Actor::APlant_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	waterStat = CreateDefaultSubobject<UNeedStat>("WaterStat");
	waterStatTimer = CreateDefaultSubobject<UTimer>("WaterStatTimer");

}

// Called when the game starts or when spawned
void APlant_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlant_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

