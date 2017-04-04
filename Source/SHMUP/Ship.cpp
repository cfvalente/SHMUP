// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "Ship.h"


// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoreMesh"));
	SetRootComponent(CoreMesh);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetVisibility(true);
	DirectionArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->Activate();

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	Forward = GetActorForwardVector();
	Right = GetActorRightVector();
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector MovementDirection = ConsumeMovementInputVector();
	AddActorLocalOffset(MovementDirection);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AShip::MoveForward(float Intensity)
{
	AddMovementInput(Forward, MaxForwardSpeed * Intensity * GetWorld()->GetDeltaSeconds());
}

void AShip::MoveRight(float Intensity)
{
	AddMovementInput(Right, MaxLateralSpeed * Intensity *GetWorld()->GetDeltaSeconds());
}
