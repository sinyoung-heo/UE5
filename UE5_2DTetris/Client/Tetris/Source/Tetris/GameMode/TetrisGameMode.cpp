// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"
#include "TetrisPawn.h"
#include "Player/TetrisPlayerController.h"
#include "UI/TetrisHUD.h"

ATetrisGameMode::ATetrisGameMode()
{
	DefaultPawnClass = ATetrisPawn::StaticClass();
	PlayerControllerClass = ATetrisPlayerController::StaticClass();
	HUDClass = ATetrisHUD::StaticClass();
}
