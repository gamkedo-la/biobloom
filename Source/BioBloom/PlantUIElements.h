// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlantUIElements.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIOBLOOM_API UPlantUIElements : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantUIElements();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description = "Place the plants description here";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
	UTexture2D* MyTexture;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
