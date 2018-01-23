// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/PlatformerGame/UI/ServerRow_WBP"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}



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

	if (!ensure(QuitGameButton != nullptr))return false;
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGameButtonPressed);

	return true;
}

void UMainMenu::HostServer() {
	UE_LOG(LogTemp, Warning, TEXT("Hosting Server!!!"));
	
	if (MenuInterface != nullptr) {
		MenuInterface->Host();
	}
}

void UMainMenu::SetServerList(TArray<FString> ServerNames) {
	
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr))return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for(const FString &ServerName : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr))return;

		Row->ServerName->SetText(FText::FromString(ServerName));

		Row->SetUp(this, i);
		++i;

		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index) {
	SelectedIndex = Index;	
}

void UMainMenu::JoinServer() {
	if (SelectedIndex.IsSet() && MenuInterface != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index is Not Set"));
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(JoinMenu != nullptr))return; 
	MenuSwitcher->SetActiveWidget(JoinMenu);
	
	if (MenuInterface != nullptr) {
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(MainMenu != nullptr))return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGameButtonPressed() {
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ConsoleCommand("quit");
}