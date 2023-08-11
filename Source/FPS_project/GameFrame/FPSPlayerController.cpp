// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include <FPS_project/GameFrame/FPSGameMode.h>
#include <EnhancedInputSubsystems.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


void AFPSPlayerController::OnEndGameCPP()
{
	UUserWidget* Widget = CreateWidget(this, ResultWidget);
	if (Widget)
	{
		Widget->AddToViewport();
	}
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(FPSInputMappingContext, 0);
	}
	UUserWidget* Widget = CreateWidget(this, GameplayWidget);
	if (Widget)
	{
		Widget->AddToViewport();
	}

	AFPSGameMode* GameMode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->OnEndGameCPP.AddUniqueDynamic(this, &AFPSPlayerController::OnEndGameCPP);
	}
}