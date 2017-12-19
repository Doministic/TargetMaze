// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success)return false;

	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (!ensure(Host != nullptr))return false;

	Join->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (!ensure(Join != nullptr))return false;

	return true;
}

void UMainMenu::HostServer() {
	UE_LOG(LogTemp, Warning, TEXT("Hosting Server Now!!!"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/PlatformerGame/Levels/Lobby?listen");
}

void UMainMenu::JoinServer() {
	UE_LOG(LogTemp, Warning, TEXT("Joining Server Now!!!"));
}

