// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisHUD.h"
#include "Blueprint/UserWidget.h"

ATetrisHUD::ATetrisHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		SceneWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Scene/WBP_ScreenWidget.WBP_ScreenWidget_C'"));
	if (SceneWidgetClassFinder.Succeeded())
	{
		SceneWidgetClass = SceneWidgetClassFinder.Class;
	}
}

void ATetrisHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ATetrisHUD::BeginPlay()
{
	Super::BeginPlay();
	CreateSceneWidget();
}

void ATetrisHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATetrisHUD::CreateSceneWidget()
{
	if (nullptr == SceneWidgetClass)
		return;

	SceneWidget = CreateWidget<UUserWidget>(GetWorld(), SceneWidgetClass);
	if (nullptr == SceneWidget)
		return;

	SceneWidget->AddToViewport();
	SceneWidget->SetVisibility(ESlateVisibility::Visible);
}
