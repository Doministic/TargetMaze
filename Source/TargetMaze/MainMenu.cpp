// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success)return false;

	if (!ensure(HostButton != nullptr))return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr))return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr))return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(ConfirmJoinButton != nullptr))return false;
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface) {
	this->MenuInterface = MenuInterface;
}

void UMainMenu::SetUp() {
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

void UMainMenu::TearDown() {
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer() {
	UE_LOG(LogTemp, Warning, TEXT("Hosting Server!!!"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/PlatformerGame/Levels/ThirdPersonExampleMap?listen");

	if (!ensure(MenuInterface != nullptr))return;
	if (MenuInterface != nullptr) {
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer() {
	UE_LOG(LogTemp, Warning, TEXT("Joining Server!!!"));

	if (!ensure(MenuInterface != nullptr))return;
	if (MenuInterface != nullptr) {
		if (!ensure(IPAddressField != nullptr))return;
		const FString Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(JoinMenu != nullptr))return; 
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(MainMenu != nullptr))return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}