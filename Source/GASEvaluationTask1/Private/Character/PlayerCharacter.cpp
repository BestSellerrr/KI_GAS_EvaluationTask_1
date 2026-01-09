// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerAttributeSet)
	{
		FString HealthString = FString::Printf(TEXT("%.1f / %.1f"), PlayerAttributeSet->GetPlayerHealth(), PlayerAttributeSet->GetPlayerMaxHealth());
		DrawDebugString(GetWorld(), GetActorLocation(), HealthString, nullptr, FColor::White, 0, true);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

