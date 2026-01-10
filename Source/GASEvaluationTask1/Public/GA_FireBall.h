// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Actor/Projectile.h"
#include "GA_FireBall.generated.h"

/**
 * 
 */
UCLASS()
class GASEVALUATIONTASK1_API UGA_FireBall : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_FireBall();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;

protected:
	AProjectile* SpawnFireBall(const FGameplayAbilityActorInfo* ActorInfo);

	UFUNCTION()
	void ApplyEffect(AActor* OtherActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AProjectile> FireBallProjectile = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> FireBallEffect = nullptr;
};
