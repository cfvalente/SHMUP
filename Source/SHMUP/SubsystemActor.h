// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SubsystemActor.generated.h"


UENUM(BlueprintType)
enum class ESubsystemEnum : uint8
{
	VE_Weapon 	UMETA(DisplayName = "Weapon"),
	VE_Misc 	UMETA(DisplayName = "Misc"),
	VE_None		UMETA(DisplayName = "None")
};


UCLASS()
class SHMUP_API ASubsystemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASubsystemActor();

	ESubsystemEnum GetSubsystemType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ESubsystemEnum ClassType = ESubsystemEnum::VE_None;
};
