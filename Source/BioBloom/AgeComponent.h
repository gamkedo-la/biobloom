// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Timer.h"
#include "AgeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIOBLOOM_API UAgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAgeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimer* ageTimer;

	UFUNCTION(BlueprintCallable)
	void Age();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
