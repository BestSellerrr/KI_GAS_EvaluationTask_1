// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASEVALUATIONTASK1_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPlayerAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData PlayerMaxHealth;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, PlayerMaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData PlayerHealth;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, PlayerHealth)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData PlayerMaxMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, PlayerMaxMana)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData PlayerMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, PlayerMana)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute|Stat")
	FGameplayAttributeData PlayerAttPower;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, PlayerAttPower)
};
