// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/R1UserWidget.h"
#include "R1InventorySlotsWidget.generated.h"

class UR1InventorySlotWidget;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class UE5_CXX_API UR1InventorySlotsWidget : public UR1UserWidget
{
	GENERATED_BODY()
	
public:
	UR1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TSubclassOf<UR1InventorySlotWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UR1InventorySlotWidget>> SlotWidgets;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;
};
