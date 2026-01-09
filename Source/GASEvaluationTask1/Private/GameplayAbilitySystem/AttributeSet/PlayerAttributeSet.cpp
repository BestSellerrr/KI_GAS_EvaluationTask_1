// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitPlayerMaxHealth(100.0f);
	InitPlayerHealth(100.0f);
	InitPlayerMaxMana(100.0f);
	InitPlayerMana(100.0f);
	InitPlayerAttPower(10.0);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetPlayerHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetPlayerMaxHealth());
	}
	if (Attribute == GetPlayerManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetPlayerMaxMana());
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetPlayerHealthAttribute())
	{
		SetPlayerHealth(FMath::Clamp(GetPlayerHealth(), 0.0f, GetPlayerMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetPlayerManaAttribute())
	{
		SetPlayerMana(FMath::Clamp(GetPlayerMana(), 0.0f, GetPlayerMaxMana()));
	}
}
