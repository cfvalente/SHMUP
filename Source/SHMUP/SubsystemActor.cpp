// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "SubsystemActor.h"


// Sets default values
ASubsystemActor::ASubsystemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ESubsystemEnum ASubsystemActor::GetSubsystemType()
{
	return ClassType;
}

// Called when the game starts or when spawned
void ASubsystemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

