// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "R1PlayerState.generated.h"

class UR1AbilitySystemComponent;
/**
 * 
 */
UCLASS()
class UE5_CXX_API AR1PlayerState : public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AR1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UR1AbilitySystemComponent> AbilitySystemComponent;
};
