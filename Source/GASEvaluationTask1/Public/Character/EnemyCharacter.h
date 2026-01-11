// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "EnemyCharacter.generated.h"

class UEnemyAttributeSet;

UCLASS()
class GASEVALUATIONTASK1_API AEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnCurrentHealthChange(const FOnAttributeChangeData& InData);
	void OnMaxHealthChange(const FOnAttributeChangeData& InData);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|UI")
	TObjectPtr<class UWidgetComponent> WidgetComponent = nullptr;
private:
	UPROPERTY()
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet = nullptr; 

};
