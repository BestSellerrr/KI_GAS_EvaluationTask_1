// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpdateWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUpdateWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GASEVALUATIONTASK1_API IUpdateWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentHealth(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentMana(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxHealth(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxMana(float InValue);
};
