// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TetrisHUD.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATetrisHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void CreateSceneWidget();

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> SceneWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> SceneWidget;
};
