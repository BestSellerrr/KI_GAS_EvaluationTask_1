// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSet/EnemyAttributeSet.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyAttributeSet)
	{
		FString HealthString = FString::Printf(TEXT("%.1f / %.1f"), EnemyAttributeSet->GetEnemyHealth(), EnemyAttributeSet->GetEnemyMaxHealth());
		DrawDebugString(GetWorld(), GetActorLocation(), HealthString, nullptr, FColor::White, 0, true);
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

