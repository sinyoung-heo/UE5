// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "R1AIController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CXX_API AR1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AR1AIController();

	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
};
