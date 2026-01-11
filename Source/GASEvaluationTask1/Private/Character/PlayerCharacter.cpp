// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"
#include "EnhancedInputComponent.h"
#include "Interface/UpdateWidgetInterface.h"
#include "UI/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"

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
	
	if (!PlayerHud)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (AHUD* HUD = PC->GetHUD())
			{
				PlayerHud = Cast<APlayerHUD>(HUD);
			}
		}
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (FireBall)
		{
			FGameplayAbilitySpecHandle GivenHandle = AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					FireBall,
					1,
					static_cast<int32>(EAbilityID::FireBall),
					this
				)
			);
		}

		FOnGameplayAttributeValueChange& OnCurrentManaChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetPlayerManaAttribute());
		OnCurrentManaChange.AddUObject(this, &APlayerCharacter::OnCurrentManaChange);

		FOnGameplayAttributeValueChange& OnMaxManaChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetPlayerMaxManaAttribute());
		OnMaxManaChange.AddUObject(this, &APlayerCharacter::OnMaxManaChange);
	}

	if (PlayerAttributeSet)
	{
		if (PlayerHud)
		{
			if (UUserWidget* WidgetInstance = PlayerHud->GetPlayerWidgetInstance())
			{
				if (WidgetInstance->GetClass()->ImplementsInterface(UUpdateWidgetInterface::StaticClass()))
				{
					IUpdateWidgetInterface::Execute_UpdateMaxMana(WidgetInstance, PlayerAttributeSet->GetPlayerMaxMana());
					IUpdateWidgetInterface::Execute_UpdateCurrentMana(WidgetInstance, PlayerAttributeSet->GetPlayerMana());
				}
			}
		}
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

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(IA_FireBall, ETriggerEvent::Started, this, &APlayerCharacter::OnAbilityFireBall);
	}
}

void APlayerCharacter::OnAbilityFireBall()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityID::FireBall));
	}
}

void APlayerCharacter::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
	if (PlayerAttributeSet && PlayerHud)
	{
		if (UUserWidget* WidgetInstance = PlayerHud->GetPlayerWidgetInstance())
		{
			if (WidgetInstance->GetClass()->ImplementsInterface(UUpdateWidgetInterface::StaticClass()))
			{
				IUpdateWidgetInterface::Execute_UpdateMaxMana(WidgetInstance, PlayerAttributeSet->GetPlayerMaxMana());
			}
		}
	}
}

void APlayerCharacter::OnCurrentManaChange(const FOnAttributeChangeData& InData)
{
	if (PlayerAttributeSet && PlayerHud)
	{
		if (UUserWidget* WidgetInstance = PlayerHud->GetPlayerWidgetInstance())
		{
			if (WidgetInstance->GetClass()->ImplementsInterface(UUpdateWidgetInterface::StaticClass()))
			{
				IUpdateWidgetInterface::Execute_UpdateCurrentMana(WidgetInstance, PlayerAttributeSet->GetPlayerMana());
			}
		}
	}
}

