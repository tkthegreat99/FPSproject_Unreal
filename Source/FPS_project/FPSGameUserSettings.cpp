// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameUserSettings.h"

float UFPSGameUserSettings::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

void UFPSGameUserSettings::SetMouseSensitivity(float Value)
{
	MouseSensitivity = Value;
}

void UFPSGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();
	MouseSensitivity = 1.0;
	AutoExposureBrightness = 1.5;
}

float UFPSGameUserSettings::GetAutoExposureBrightness() const
{
	return AutoExposureBrightness;
}

void UFPSGameUserSettings::SetAutoExposureBrightness(float Value)
{
	AutoExposureBrightness = Value;
}