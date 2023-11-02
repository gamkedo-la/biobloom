// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantUIWidget.h"


bool UPlantUIWidget::SetPlantImage(UTexture2D* image)
{

	PlantImage->SetBrushFromTexture(image);
	return true;
}

bool UPlantUIWidget::SetPlantDescription(FText text)
{
	PlantDescriptionText->SetText(text);
	return true;
}
