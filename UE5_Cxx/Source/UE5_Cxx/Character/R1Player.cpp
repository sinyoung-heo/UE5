// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/R1PlayerController.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Attribute/R1PlayerSet.h"
#include "Player/R1PlayerState.h"

AR1Player::AR1Player()
	: Super()
{
	// Don't rotate character to camera direction
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AR1Player::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	//TEMP
	if (TestEffect && AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		// Handle
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(TestEffect,1, EffectContext);

		// Apply
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void AR1Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystem();
}

void AR1Player::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	if (auto PS = GetPlayerState<AR1PlayerState>())
	{
		AbilitySystemComponent = Cast<UR1AbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetR1PlayerSet();
	}
}

void AR1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AR1Player::HandleGamePlayEvent(FGameplayTag EventTag)
{
	AR1PlayerController* PC = Cast<AR1PlayerController>(GetController());
	if (PC)
	{
		PC->HandleGamePlayEvent(EventTag);
	}
}

void AR1Player::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap"));
}
