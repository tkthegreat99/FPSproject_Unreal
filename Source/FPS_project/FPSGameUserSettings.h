// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "FPSGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API UFPSGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	float GetMouseSensitivity() const;
	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(float Value);

	float GetAutoExposureBrightness() const;
	void SetAutoExposureBrightness(float Value);

protected:
	virtual void SetToDefaults() override;


protected:
	UPROPERTY(Config)
	float MouseSensitivity;

	UPROPERTY(Config)
	float AutoExposureBrightness;
};
