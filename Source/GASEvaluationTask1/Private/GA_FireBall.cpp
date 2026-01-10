// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_FireBall.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UGA_FireBall::UGA_FireBall()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_FireBall::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	if (!FireBallProjectile ||
		!FireBallEffect ||
		!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AProjectile* Projectile = SpawnFireBall(ActorInfo);
	if (Projectile)
		Projectile->OnProjectileBeginOverlap.AddDynamic(this, &UGA_FireBall::ApplyEffect);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

AProjectile* UGA_FireBall::SpawnFireBall(const FGameplayAbilityActorInfo* ActorInfo)
{
	ACharacter* Avatar = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	UWorld* World = Avatar->GetWorld();
	if (!World)
		return nullptr;

	FVector SpawnLocation = Avatar->GetActorLocation() + Avatar->GetActorForwardVector();
	FRotator SpawnRotation = Avatar->GetActorRotation();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Avatar;
	SpawnParams.Instigator = Cast<APawn>(Avatar);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (FireBallProjectile)
	{
		AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(
			FireBallProjectile,
			SpawnTransform,
			SpawnParams
		);

		return SpawnedProjectile;
	}

	return nullptr;
}

void UGA_FireBall::ApplyEffect(AActor* OtherActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!TargetASC)
		return;

	UAbilitySystemComponent* SourceASC = nullptr;
	if (GetCurrentActorInfo() && GetCurrentActorInfo()->AbilitySystemComponent.IsValid())
		SourceASC = GetCurrentActorInfo()->AbilitySystemComponent.Get();
	if (!SourceASC)
		return;

	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecAbility = SourceASC->MakeOutgoingSpec(FireBallEffect, GetAbilityLevel(), EffectContext);
	FGameplayEffectSpecHandle EffectSpecDebuff = SourceASC->MakeOutgoingSpec(BurnEffect, GetAbilityLevel(), EffectContext);
	if (EffectSpecAbility.IsValid())
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecAbility.Data.Get());
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecDebuff.Data.Get());
	}
}
