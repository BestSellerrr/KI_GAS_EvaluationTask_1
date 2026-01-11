// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Cue/GCNA_Burn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_Burn::AGCNA_Burn()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Debuff.Burn"));
	bAutoDestroyOnRemove = true;
}

bool AGCNA_Burn::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}

	if (MyTarget)
	{
		SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			VFX,
			MyTarget->GetActorLocation(),
			MyTarget->GetActorRotation()
		);
		return true;
	}
	return false;
}

bool AGCNA_Burn::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
