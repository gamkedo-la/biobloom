// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeedActor.generated.h"

UCLASS()
class BIOBLOOM_API ASeedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeedActor();

public:
	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	USceneComponent* defaultSceneRoot;

	UPROPERTY(EditAnywhere, Instanced, Category = "Components", BlueprintReadWrite)
	UStaticMeshComponent* seedMesh;


public:
	UFUNCTION(BlueprintCallable)
	void GrowSeed();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
