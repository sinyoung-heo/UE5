// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "R1Actor.h"

// Sets default values
AMainActor::AMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AR1Actor> FindClass(TEXT("/Script/Engine.Blueprint'/Game/_Rookiss/BP_R1Actor.BP_R1Actor_C'"));
	if (FindClass.Succeeded())
	{
		ActorClass = FindClass.Class;
	}
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);
	
	//Actor = GetWorld()->SpawnActor<AR1Actor>(Location, Rotation);
	Actor = Cast<AR1Actor>(GetWorld()->SpawnActor(ActorClass));

	// GetWorld()->DestroyActor(Actor);	// Áï½Ã ÆÄ±«
	Actor->SetLifeSpan(5.0f);	// nÃÊ ÈÄ ÆÄ±«
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

