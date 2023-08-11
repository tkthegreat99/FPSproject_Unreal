// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCheatManager.h"
#include <FPS_project/FPSGameUserSettings.h>

void UFPSCheatManager::FPSSetResolution(int32 Width, int32 Height)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if(UserSettings)
	{
		UserSettings->SetScreenResolution(FIntPoint(Width, Height));
		UserSettings->ApplySettings(false);
	}
}

void UFPSCheatManager::FPSSetWindowMode(int32 WindowMode)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		EWindowMode::Type NewWindowMode = (EWindowMode::Type)WindowMode;
		UserSettings->SetFullscreenMode(NewWindowMode);
		UserSettings->ApplySettings(false);
	}
}

void UFPSCheatManager::FPSSetMouseSensitivity(float Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetMouseSensitivity(Value);
		UserSettings->ApplySettings(false);
	}
}

void UFPSCheatManager::FPSSetBrightness(float Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetAutoExposureBrightness(Value);
		UserSettings->ApplySettings(false);
	}
}