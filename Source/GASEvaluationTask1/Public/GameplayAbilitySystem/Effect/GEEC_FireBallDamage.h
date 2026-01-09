// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_FireBallDamage.generated.h"

/**
 * 
 */
UCLASS()
class GASEVALUATIONTASK1_API UGEEC_FireBallDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGEEC_FireBallDamage();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MinimumDamage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float DamageMultiplier = 2.0f;

private:
	FGameplayTag Tag_DebuffBurn;
	FGameplayTag Tag_ElementFire;
	
};
