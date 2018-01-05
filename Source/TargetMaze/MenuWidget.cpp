// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface) {
	this->MenuInterface = MenuInterface;
}

void UMenuWidget::SetUp() {
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	FInputModeUIOnly InputData;
	InputData.SetWidgetToFocus(this->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::TearDown() {
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}


