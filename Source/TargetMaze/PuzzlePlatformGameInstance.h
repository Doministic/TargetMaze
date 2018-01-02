// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TARGETMAZE_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	

public:
	UPuzzlePlatformGameInstance();

	virtual void Init();
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	TSubclassOf<class UUserWidget> MenuClass;

private:
	class UMainMenu* Menu;
};					 
