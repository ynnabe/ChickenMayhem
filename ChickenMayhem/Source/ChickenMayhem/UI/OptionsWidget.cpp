// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OptionsWidget.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	for(int i = 0; i < 5; i++)
	{
		FString TempScalability = Scalability::GetScalabilityNameFromQualityLevel(i).ToString();
		GraphicsQualityComboBox->AddOption(TempScalability);
	}
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	int32 CurrentScabilityLevel = GameUserSettings->GetOverallScalabilityLevel();
	GraphicsQualityComboBox->SetSelectedIndex(CurrentScabilityLevel);

	CurrentWindowMode = GameUserSettings->GetFullscreenMode();

	if(!Resolutions.Contains(GameUserSettings->GetDesktopResolution()))
	{
		Resolutions.Add(GameUserSettings->GetDesktopResolution());
	}

	for (auto Resolution : Resolutions)
	{
		ResolutionComboBox->AddOption(Resolution.ToString());
	}

	ResolutionComboBox->SetSelectedIndex(ResolutionComboBox->GetOptionCount() - 1);
	WindowModeComboBox->SetSelectedIndex(CurrentWindowMode);
}

void UOptionsWidget::ApplySettings()
{
	UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();
	
	switch(GraphicsQualityComboBox->GetSelectedIndex())
	{
		case EQuality::Low:
			{
				GameUserSettings->SetOverallScalabilityLevel(0);
				break;
			}
		case EQuality::Medium:
			{
				GameUserSettings->SetOverallScalabilityLevel(1);
				break;
			}
		case EQuality::High:
			{
				GameUserSettings->SetOverallScalabilityLevel(2);
				break;
			}
		case EQuality::Epic:
			{
				GameUserSettings->SetOverallScalabilityLevel(3);
				break;
			}
		case EQuality::Cinematic:
			{
				GameUserSettings->SetOverallScalabilityLevel(4);
			}
	}

	switch(CurrentWindowMode)
	{
	case 0:
		{
			GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
			break;
		}
	case 1:
		{
			GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
			break;
		}
	case 2:
		{
			GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
			break;
		}
	}

	GameUserSettings->SetScreenResolution(Resolutions[ResolutionComboBox->GetSelectedIndex()]);
	
	GameUserSettings->ApplySettings(true);
}

void UOptionsWidget::OnChangeWindowMode()
{
	CurrentWindowMode = StaticCast<EWindowMode::Type>(WindowModeComboBox->GetSelectedIndex());
}
