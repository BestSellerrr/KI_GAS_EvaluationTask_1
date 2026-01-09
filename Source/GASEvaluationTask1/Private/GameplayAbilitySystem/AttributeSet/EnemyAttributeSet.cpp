// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AttributeSet/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitEnemyMaxHealth(100.0f);
	InitEnemyHealth(100.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetEnemyHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetEnemyMaxHealth());
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetEnemyHealthAttribute())
	{
		SetEnemyHealth(FMath::Clamp(GetEnemyHealth(), 0.0f, GetEnemyMaxHealth()));
	}
}
