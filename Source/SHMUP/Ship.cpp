// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "SubsystemActor.h"
#include "WeaponActor.h"
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

	ParseChildActors();
	IgnoreCollisionWithChildActors();
}

void AShip::ParseChildActors()
{
	TArray<AActor *> ChildActors;
	this->GetAllChildActors(ChildActors);
	for (int32 i = 0; i < ChildActors.Num(); i++)
	{
		ASubsystemActor *SubsystemActor = nullptr;
		SubsystemActor = Cast<ASubsystemActor>(ChildActors[i]);
		if (SubsystemActor != nullptr)
		{
			AWeaponActor *WeaponActor = nullptr;
			switch (SubsystemActor->GetSubsystemType())
			{
			case ESubsystemEnum::VE_Weapon:
				WeaponActor = Cast<AWeaponActor>(SubsystemActor);
				if (WeaponActor != nullptr)
				{
					MainWeaponSubsystem.Add(WeaponActor);
				}
				break;
			case ESubsystemEnum::VE_Misc:
				break;
			case ESubsystemEnum::VE_None:
				break;
			}
		}
	}
}

void AShip::IgnoreCollisionWithChildActors()
{
	for (int32 i = 0; i < MainWeaponSubsystem.Num(); i++)
	{
		MoveIgnoreActorAdd(MainWeaponSubsystem[i]);
	}
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector MovementDirection = ConsumeMovementInputVector();
	
	AddActorLocalOffset(MovementDirection, true);
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

void AShip::Fire()
{
	for (int32 i = 0; i < MainWeaponSubsystem.Num(); i++)
	{
		MainWeaponSubsystem[i]->Fire();
	}
}

