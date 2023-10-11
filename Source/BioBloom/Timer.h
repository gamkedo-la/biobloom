// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/App.h"
#include "Components/ActorComponent.h"
#include "Timer.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BIOBLOOM_API UTimer : public UActorComponent
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void ProgressTime();  // Removed static
public:	

	// Sets default values for this component's properties
	UTimer();
	//progress the currenttime the timer has been active

#pragma region Events
	UFUNCTION(BlueprintImplementableEvent)
	void MaxTimeReached();
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fMaxTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fCurrentTime;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
