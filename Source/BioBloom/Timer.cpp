// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"


void UTimer::ProgressTime()
{
	//add worlds delta time to current time
	fCurrentTime += GetWorld()->GetDeltaSeconds();

	if (fCurrentTime < fMaxTime)
	{
		//see delta time
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(fCurrentTime));

	}
	else
	{

		MaxTimeReached();


		//Broadcast event to all subscribers
		TimerFinished.Broadcast();

		//set current time back to zero
		fCurrentTime = 0;
	}

}

void UTimer::PauseTimer(bool pause)
{
	TimerPaused = pause;
}

void UTimer::ResetTimer()
{
	fCurrentTime = 0;
}

// Sets default values for this component's properties
UTimer::UTimer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTimer::BeginPlay()
{
	Super::BeginPlay();
	TimerPaused = false;
	// ...
	
}


// Called every frame
void UTimer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TimerPaused)
		ProgressTime();

	// ...
}

