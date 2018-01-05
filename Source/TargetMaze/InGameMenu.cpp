// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(ResumeButton != nullptr))return false;
	ResumeButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseMenu);

	if (!ensure(QuitButton != nullptr))return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMainMenu);

	return true;
}

void UInGameMenu::CloseMenu() {
	TearDown();
}

void UInGameMenu::ReturnToMainMenu() {
	if (MenuInterface != nullptr) {
		MenuInterface->LoadMainMenu();
	}
}