// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "FPSCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API UFPSCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(exec)
	void FPSSetResolution(int32 Width, int32 Height);
	UFUNCTION(exec)
	void FPSSetWindowMode(int32 WindowMode);
	UFUNCTION(exec)
	void FPSSetMouseSensitivity(float Value);
	UFUNCTION(exec)
	void FPSSetBrightness(float Value);
};