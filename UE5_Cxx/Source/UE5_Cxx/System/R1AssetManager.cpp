// Fill out your copyright notice in the Description page of Project Settings.


#include "R1AssetManager.h"
#include "R1LogChannels.h"

UR1AssetManager::UR1AssetManager()
{
}

UR1AssetManager& UR1AssetManager::Get()
{
	if (UR1AssetManager* Singleton = Cast<UR1AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogR1, Fatal, TEXT("Can't find UR1AssetMansager"));
	return *NewObject<UR1AssetManager>();
}
