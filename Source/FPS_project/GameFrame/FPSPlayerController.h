// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <InputMappingContext.h>
#include <FPS_project/Widget/FPSGameplayWidget.h>
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnEndGameCPP();
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> FPSInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameplayWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ResultWidget;
};