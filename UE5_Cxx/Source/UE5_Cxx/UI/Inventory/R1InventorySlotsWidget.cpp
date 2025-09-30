// Fill out your copyright notice in the Description page of Project Settings.


#include "R1InventorySlotsWidget.h"
#include "Components/UniformGridPanel.h"
#include "R1InventorySlotWidget.h"

UR1InventorySlotsWidget::UR1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UR1InventorySlotWidget> FindSlotWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'"));
	if (FindSlotWidgetClass.Succeeded())
	{
		SlotWidgetClass = FindSlotWidgetClass.Class;
	}
}

void UR1InventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const int X_COUNT = 10;
	const int Y_COUNT = 5;

	SlotWidgets.SetNum(X_COUNT * Y_COUNT);
	for (int32 y = 0; y < Y_COUNT; ++y)
	{
		for (int32 x = 0; x < X_COUNT; ++x)
		{
			int32 index = y * X_COUNT + x;

			auto SlotWidget = CreateWidget<UR1InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			SlotWidgets[index] = SlotWidget;
			GridPanel_Slots->AddChildToUniformGrid(SlotWidget, y, x);
		}
	}
}
