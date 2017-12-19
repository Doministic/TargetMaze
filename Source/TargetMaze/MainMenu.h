// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class TARGETMAZE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


private:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Host;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();
};