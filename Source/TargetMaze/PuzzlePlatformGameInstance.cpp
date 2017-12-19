// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "PlatformTrigger.h"

#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance() {

	ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/PlatformerGame/Blueprints/BP_PlatformTrigger"));
	if (!ensure(PlatformTriggerBPClass.Class != nullptr))return;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/PlatformerGame/UI/MainMenu_WBP"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;


}																																								   

void UPuzzlePlatformGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadMenu() {
	if (!ensure(MenuClass != nullptr))return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);

	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	FInputModeUIOnly InputData;
	InputData.SetWidgetToFocus(Menu->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;
}


void UPuzzlePlatformGameInstance::Host() {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/PlatformerGame/Levels/Lobby");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address) {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

}


