// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Effect/GEEC_FireBallDamage.h"
#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"
#include "GameplayAbilitySystem/AttributeSet/EnemyAttributeSet.h"

struct FFireBallDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnemyHealth)
	DECLARE_ATTRIBUTE_CAPTUREDEF(PlayerAttPower)

	FFireBallDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, EnemyHealth, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, PlayerAttPower, Source, true);
	}
};

struct FFireBallDamageStatics& FireBallDamageStatics()
{
	static FFireBallDamageStatics Statics;
	return Statics;
};

UGEEC_FireBallDamage::UGEEC_FireBallDamage()
{
	RelevantAttributesToCapture.Add(FireBallDamageStatics().PlayerAttPowerDef);
	RelevantAttributesToCapture.Add(FireBallDamageStatics().EnemyHealthDef);

	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));
	Tag_ElementFire = FGameplayTag::RequestGameplayTag(FName("Element.Fire"));
}

void UGEEC_FireBallDamage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

		float Damage = MinimumDamage;

		FAggregatorEvaluateParameters EvaluateParameters;
		EvaluateParameters.SourceTags = SourceTags;
		EvaluateParameters.TargetTags = TargetTags;
		float AttackPower = 0.0f;
		bool Result = ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			FireBallDamageStatics().PlayerAttPowerDef,
			EvaluateParameters,
			AttackPower
		);
		if (Result)
		{
			Damage = AttackPower;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("GEEC_FireBallDamage : Fail PlayerAttackPower"));
		}

		if (SourceTags && SourceTags->HasTag(Tag_ElementFire) && 
			TargetTags && TargetTags->HasTag(Tag_DebuffBurn))
		{
			Damage *= DamageMultiplier;
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireBallDamageStatics().EnemyHealthProperty,
					EGameplayModOp::Additive,
					-Damage
				)
			);
		}
	}
}
