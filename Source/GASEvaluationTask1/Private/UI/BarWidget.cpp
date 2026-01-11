// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBarWidget::SetProgressBarColor(FLinearColor InColor)
{
	ProgressBar->SetFillColorAndOpacity(InColor);
}

void UBarWidget::UpdateCurrent_Implementation(float InValue)
{
	CurrentText->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	CurrentValue = InValue;
	ProgressBar->SetPercent(CurrentValue / MaxValue);
}

void UBarWidget::UpdateMax_Implementation(float InValue)
{
	MaxText->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	MaxValue = InValue;
	ProgressBar->SetPercent(CurrentValue / MaxValue);
}
