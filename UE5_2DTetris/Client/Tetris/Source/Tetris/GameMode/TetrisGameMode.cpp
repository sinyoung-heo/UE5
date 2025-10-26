// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"
#include "TetrisPawn.h"
#include "Player/TetrisPlayerController.h"

ATetrisGameMode::ATetrisGameMode()
{
	DefaultPawnClass = ATetrisPawn::StaticClass();
	PlayerControllerClass = ATetrisPlayerController::StaticClass();
}
