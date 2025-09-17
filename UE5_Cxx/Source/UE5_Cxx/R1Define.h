// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Moving,
	SKill,
	Dead,
};

#define D(x) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,x); }