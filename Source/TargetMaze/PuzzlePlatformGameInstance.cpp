// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MainMenu.h"
#include "MenuWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance() {

	ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/PlatformerGame/Blueprints/BP_PlatformTrigger"));
	if (!ensure(PlatformTriggerBPClass.Class != nullptr))return;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/PlatformerGame/UI/MainMenu_WBP"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/PlatformerGame/UI/InGame_WBP"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;

}																																								   

void UPuzzlePlatformGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadMenu() {
	
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(MenuClass != nullptr))return;

	
	Menu->SetUp();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::InGameLoadMenu() {
	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenuClass != nullptr))return;

	Menu->SetUp();
	Menu->SetMenuInterface(this);

}

void UPuzzlePlatformGameInstance::Host() {

	if (Menu != nullptr) {
		Menu->TearDown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/PlatformerGame/Levels/ThirdPersonExampleMap");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address) {
	if (Menu != nullptr) {
		Menu->TearDown();
	}
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::LoadMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ClientTravel("/Game/PlatformerGame/Levels/MainMenu", ETravelType::TRAVEL_Absolute);
}


