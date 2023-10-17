// Fill out your copyright notice in the Description page of Project Settings.

/*
	This script is for holding simple stats 
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Timer.h"
#include "NeedStat.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BIOBLOOM_API UNeedStat : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NeedAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float statMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimer* statTimer;

	UNeedStat();

	UFUNCTION(BlueprintCallable)
	void TakeNeed();

	UFUNCTION(BlueprintCallable)
	void ChangeStat(float amountChanged);

	UFUNCTION(BlueprintCallable)
	void SetTimer(UTimer* timer);

	UFUNCTION(BlueprintCallable)
	float GetStat();

	UFUNCTION(BlueprintCallable)
	void SetStat(float SetAmount);

	UFUNCTION(BlueprintCallable)
	void SetStatMax(float SetAmount);
protected:


	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
