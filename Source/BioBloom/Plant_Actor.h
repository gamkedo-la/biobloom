// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeedStat.h"
#include "Plant_Actor.generated.h"

UCLASS(Blueprintable,ClassGroup = (Custom), meta = (BlueprintSpawnableActor))
class BIOBLOOM_API APlant_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant_Actor();

	UPROPERTY(Instanced,EditAnywhere, Category = "Components", BlueprintReadWrite)
	class UNeedStat* waterStat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
