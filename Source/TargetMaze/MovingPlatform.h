// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class TARGETMAZE_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	void AddActiveTrigger();
	void RemoveActiveTrigger();

	
protected:
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float speed = 10.0f;
	
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetLocation;

	

private:

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTrigger = 1;
};
