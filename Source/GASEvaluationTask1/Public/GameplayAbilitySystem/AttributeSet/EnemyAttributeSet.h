// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASEVALUATIONTASK1_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEnemyAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData EnemyMaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, EnemyMaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData EnemyHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, EnemyHealth)
};
