// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "PlantUIWidget.h"
#include "PlantUIElements.h"
#include "Timer.h"
#include "AgeComponent.h"
#include "NeedStat.h"
#include "Plant_Actor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrowDelegate);

UCLASS(Blueprintable,ClassGroup = (Custom), meta = (BlueprintSpawnableActor))
class BIOBLOOM_API APlant_Actor : public AActor
{
	GENERATED_BODY()
	float growth;

	UFUNCTION()
	void Grow();
public:	
	// Sets default values for this actor's properties
	APlant_Actor();

#pragma region Health

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlantHealth = 1;

	UFUNCTION()
	float GetHealth();
	UFUNCTION()
	void SetHealth(float Health);
	UFUNCTION()
	bool Die();
#pragma endregion


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DegradationAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float growRate;


	UFUNCTION(BlueprintImplementableEvent)
	void PlantGrewEvent();

	UPROPERTY(BlueprintAssignable)
	FGrowDelegate PlantGrewDelegate;

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	UStaticMeshComponent* plantMesh;
#pragma region UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UWidgetComponent* WorldSpaceWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	UPlantUIElements* plantUIElements;
#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	UAgeComponent* ageComponent;

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	UNeedStat* waterStat;

	UPROPERTY(EditAnywhere, Category = "Components", BlueprintReadWrite)
	UTimer* growthTimer;

	UPROPERTY(EditAnywhere, Instanced)
	TArray <class UNeedStat*> needs;

	UFUNCTION(BlueprintCallable)
	void SetPlantSize(const float size);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
