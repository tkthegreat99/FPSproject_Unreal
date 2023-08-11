// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FPSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API UFPSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<float> ScoresCPP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> TimesCPP;


	
};
