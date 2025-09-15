// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1Define.h"
#include "R1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class UE5_CXX_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	void TickCursorTrace();
	void ChaseTargetAndAttack();

private:
	// Input handlers for SetDestination action
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	ECreatureState GetCreatureState();
	void SetCreatureState(ECreatureState InState);

public:
	// Time Threshold to know if it was a short press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	// FX Class that we will spawn when clicking
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed
	bool bMousePressed = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Character> TargetActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Character> HighlightActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Player> R1Player;
};
