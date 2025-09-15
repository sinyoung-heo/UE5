// Fill out your copyright notice in the Description page of Project Settings.


#include "R1Monster.h"

AR1Monster::AR1Monster()
	: Super()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AR1Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AR1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
