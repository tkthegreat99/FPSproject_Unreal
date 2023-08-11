// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSUserSettingsWidget.h"
#include <FPS_project/FPSGameUserSettings.h>

void UFPSUserSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitComponents();
	BindEvents();
}

void UFPSUserSettingsWidget::InitComponents()
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		FIntPoint Resolution = UserSettings->GetScreenResolution();
		EditWidth->SetText(FText::AsNumber(Resolution.X));
		EditHeight->SetText(FText::AsNumber(Resolution.Y));

		EWindowMode::Type WindowMode = UserSettings->GetFullscreenMode();
		switch (WindowMode)
		{
		case EWindowMode::Fullscreen:
			ButtonFullscreen->SetIsEnabled(false);
			break;
		case EWindowMode::WindowedFullscreen:
			ButtonBorderless->SetIsEnabled(false);
			break;
		case EWindowMode::Windowed:
			ButtonWindow->SetIsEnabled(false);
			break;
		}

		float MouseSensitivity = UserSettings->GetMouseSensitivity();
		SliderMouseSensitibity->SetValue(MouseSensitivity);
		TextMouseSensitivity->SetText(FText::AsNumber(MouseSensitivity));

		float AutoExposureBrightness = UserSettings->GetAutoExposureBrightness();
		float Brightness = (AutoExposureBrightness * -1.0) + 5.0;
		SliderBrightness->SetValue(Brightness);
		TextBrightness->SetText(FText::AsNumber(Brightness));
	}
}

void UFPSUserSettingsWidget::BindEvents()
{
	EditWidth->OnTextChanged.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnWidthChanged);
	EditHeight->OnTextChanged.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnHeightChanged);
	ButtonFullscreen->OnClicked.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnFullscreenClicked);
	ButtonBorderless->OnClicked.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnBorderlessClicked);
	ButtonWindow->OnClicked.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnWindowedClicked);
	SliderMouseSensitibity->OnValueChanged.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnMouseSensitivityChanged);
	SliderBrightness->OnValueChanged.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnBrightnessChanged);
	ButtonExit->OnClicked.AddUniqueDynamic(this, &UFPSUserSettingsWidget::OnExitClicked);
}

void UFPSUserSettingsWidget::OnWidthChanged(const FText& Text)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		if (Text.IsNumeric())
		{
			FString String = Text.ToString();
			FIntPoint Resolution = UserSettings->GetScreenResolution();
			int32 Width = FCString::Atoi(*String);
			int32 Height = Resolution.Y;
			UserSettings->SetScreenResolution(FIntPoint(Width, Height));
			UserSettings->ApplySettings(false);
		}
	}
}

void UFPSUserSettingsWidget::OnHeightChanged(const FText& Text)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		if (Text.IsNumeric())
		{
			FString String = Text.ToString();
			FIntPoint Resolution = UserSettings->GetScreenResolution();
			int32 Width = Resolution.X;
			int32 Height = FCString::Atoi(*String);
			UserSettings->SetScreenResolution(FIntPoint(Width, Height));
			UserSettings->ApplySettings(false);
		}
	}
}

void UFPSUserSettingsWidget::OnFullscreenClicked()
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		UserSettings->ApplySettings(false);

		ButtonFullscreen->SetIsEnabled(false);
		ButtonBorderless->SetIsEnabled(true);
		ButtonWindow->SetIsEnabled(true);
	}
}

void UFPSUserSettingsWidget::OnBorderlessClicked()
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		UserSettings->ApplySettings(false);

		ButtonFullscreen->SetIsEnabled(true);
		ButtonBorderless->SetIsEnabled(false);
		ButtonWindow->SetIsEnabled(true);
	}
}

void UFPSUserSettingsWidget::OnWindowedClicked()
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		UserSettings->ApplySettings(false);

		ButtonFullscreen->SetIsEnabled(true);
		ButtonBorderless->SetIsEnabled(true);
		ButtonWindow->SetIsEnabled(false);
	}
}

void UFPSUserSettingsWidget::OnMouseSensitivityChanged(float Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		UserSettings->SetMouseSensitivity(Value);
		UserSettings->ApplySettings(false);

		TextMouseSensitivity->SetText(FText::AsNumber(Value));
	}
}

void UFPSUserSettingsWidget::OnBrightnessChanged(float Value)
{
	UFPSGameUserSettings* UserSettings = Cast<UFPSGameUserSettings>(GEngine->GetGameUserSettings());
	if (UserSettings)
	{
		float AutoExposureBrightness = (Value - 5.0) * -1.0;
		
		UserSettings->SetAutoExposureBrightness(AutoExposureBrightness);
		UserSettings->ApplySettings(false);

		TextBrightness->SetText(FText::AsNumber(Value));
	}
}

void UFPSUserSettingsWidget::OnExitClicked()
{
	RemoveFromParent();
}