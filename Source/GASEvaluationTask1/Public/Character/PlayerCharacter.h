// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PlayerCharacter.generated.h"

class UPlayerAttributeSet;

UENUM(BlueprintType)
enum class EAbilityID : uint8
{
	FireBall
};

UCLASS()
class GASEVALUATIONTASK1_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAbilityFireBall();

	void OnMaxManaChange(const FOnAttributeChangeData& InData);
	void OnCurrentManaChange(const FOnAttributeChangeData& InData);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|Ability")
	TSubclassOf<UGameplayAbility> FireBall = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|Input")
	TObjectPtr<class UInputAction> IA_FireBall = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet = nullptr;

	UPROPERTY()
	TObjectPtr<class APlayerHUD> PlayerHud = nullptr;
};
