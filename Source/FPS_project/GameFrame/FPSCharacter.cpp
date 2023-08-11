// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "GameFramework/Character.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>
#include <FPS_project/FPSGameUserSettings.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShadowBodyCPP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShadowBodyCPP"));
	if (ShadowBodyCPP)
	{
		ShadowBodyCPP->SetupAttachment(RootComponent);
		WeaponInBackCPP = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponInBackCPP"));
		if (WeaponInBackCPP)
		{
			WeaponInBackCPP->SetupAttachment(ShadowBodyCPP);
		}
		
	}
	LowerBodyCPP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyCPP"));
	if (LowerBodyCPP)
	{
		LowerBodyCPP->SetupAttachment(RootComponent);
	}
	

	CameraCPP = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCPP"));
	if (CameraCPP)
	{
		CameraCPP->SetupAttachment(RootComponent);
		FirstPersonCPP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonCPP"));
		if (FirstPersonCPP)
		{
			FirstPersonCPP->SetupAttachment(CameraCPP);
			WeaponInHandCPP = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponInHandCPP"));
			if (WeaponInHandCPP)
			{
				WeaponInHandCPP->SetupAttachment(FirstPersonCPP);
			}
		}
	}
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AFPSCharacter::TickBrightness()
{
	float Brightness = 0.0;
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		Brightness = UserSettings->GetAutoExposureBrightness();
	}
	if (CameraCPP)
	{
		FPostProcessSettings Settings = CameraCPP->PostProcessSettings;
		Settings.AutoExposureMinBrightness = Brightness;
		Settings.AutoExposureMaxBrightness = Brightness;
		CameraCPP->PostProcessSettings = Settings;
	}
}

void AFPSCharacter::OnTriggerRun(const FInputActionValue& Value)
{
	IsRunPressedCPP = Value.Get<bool>();
}

void AFPSCharacter::OnTriggerTurnYaw(const FInputActionValue& Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		float Yaw = UserSettings->GetMouseSensitivity() * Value.Get<float>();
		AddControllerYawInput(Yaw);
	}
}

void AFPSCharacter::OnTriggerTurnPitch(const FInputActionValue& Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		float Pitch = UserSettings->GetMouseSensitivity() * Value.Get<float>();
		AddControllerPitchInput(Pitch);
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickBrightness();
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RunInputAction, ETriggerEvent::Triggered, this, &AFPSCharacter::OnTriggerRun);
		EnhancedInputComponent->BindAction(TurnPitchInputAction, ETriggerEvent::Triggered, this, &AFPSCharacter::OnTriggerTurnPitch);
		EnhancedInputComponent->BindAction(TurnYawInputAction, ETriggerEvent::Triggered, this, &AFPSCharacter::OnTriggerTurnYaw);
	}

}

float AFPSCharacter::GetSpeedCPP() const
{
	return GetVelocity().Length();
}

bool AFPSCharacter::CanRunCPP() const
{
	return (MoveForwardValueCPP > 0.0) && IsRunPressedCPP;
}

void AFPSCharacter::TickRunCPP()
{
	if (CanRunCPP())
	{
		switch (StateCPP)
		{
		case StateOfCharacterCPP::Idle:
			StateCPP = StateOfCharacterCPP::Running;
			GetCharacterMovement()->MaxWalkSpeed *= 2.0;
		}

	}
	else
	{
		switch (StateCPP)
		{
		case StateOfCharacterCPP::Running:
			StateCPP = StateOfCharacterCPP::Idle;
			GetCharacterMovement()->MaxWalkSpeed *= 0.5;
		}
	}
}

void AFPSCharacter::OnFootstepLeftCPP()
{
	UGameplayStatics::PlaySoundAtLocation(this, FootstepLeftSoundCPP, LowerBodyCPP->GetSocketLocation("foot_l"));
}

