// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class GASEVALUATIONTASK1_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	TSubclassOf<UUserWidget> GetPlayerWidget() {
		return PlayerWidget;
	}

	UUserWidget* GetPlayerWidgetInstance() const {
		return PlayerWidgetInstance;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerWidget = nullptr;
	
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerWidgetInstance = nullptr;

public:
	void SetPlayerWidgetInstance(UUserWidget* InWidget) { PlayerWidgetInstance = InWidget; }
	
};
