// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedStat.h"

// Sets default values for this component's properties
UNeedStat::UNeedStat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UNeedStat::TakeNeed()
{
	ChangeStat(-NeedAmount);
}


void UNeedStat::ChangeStat(float amountChanged)
{
	currentStat += amountChanged;
	if (currentStat > statMax)
		currentStat = statMax;

	if (currentStat < 0)
		currentStat = 0;
}

void UNeedStat::SetTimer(UTimer* timer)
{
	statTimer = timer;
}

float UNeedStat::GetStat()
{
	return currentStat;
}

void UNeedStat::SetStat(float SetAmount)
{
	if (currentStat > statMax)
		currentStat = statMax;

	if (currentStat < 0)
		currentStat = 0;
}

void UNeedStat::SetStatMax(float SetAmount)
{
	statMax = SetAmount;
}

// Called when the game starts
void UNeedStat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNeedStat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

