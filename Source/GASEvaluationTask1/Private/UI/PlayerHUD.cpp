// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"
#include "Blueprint/UserWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidget)
	{
		if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidget))
		{
			SetPlayerWidgetInstance(Widget);
			Widget->AddToViewport();
		}
	}
}
