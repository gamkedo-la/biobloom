// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "PlantUIWidget.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class BIOBLOOM_API UPlantUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool SetPlantImage(UTexture2D* image);

	bool SetPlantDescription(FText text);

	UPROPERTY(meta = (BindWidget))
	UImage* PlantImage;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* PlantDescriptionText;
};
