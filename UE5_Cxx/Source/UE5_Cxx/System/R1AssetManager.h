// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "R1AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UE5_CXX_API UR1AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UR1AssetManager();

	static UR1AssetManager& Get();
};
