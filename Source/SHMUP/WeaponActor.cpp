// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "Bullet.h"
#include "WeaponActor.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoreMesh"));
	SetRootComponent(CoreMesh);
	CoreMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ClassType = ESubsystemEnum::VE_Weapon;
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeaponActor::Fire()
{
	float ShotTime = GetWorld()->GetRealTimeSeconds();
	if (ShotTime >= FiringCooldown + LastShotTime)
	{
		LastShotTime = ShotTime;

		if (UseMuzzleLocation)
		{
			for (int32 i = 0; i < BulletTypes.Num(); i++)
			{
				if (BulletTypes[i] != nullptr)
				{
					FActorSpawnParameters params;
					params.Owner = GetParentActor();
					GetWorld()->SpawnActor<ABullet>(BulletTypes[i], GetTransform()+MuzzleTransform, params);
				}
			}
		}
		else
		{
			if (BulletTypes.Num() == BulletCustomSpawnTransform.Num())
			{
				for (int32 i = 0; i < BulletTypes.Num(); i++)
				{
					if (BulletTypes[i] != nullptr)
					{
						FActorSpawnParameters params;
						params.Owner = GetParentActor();
						GetWorld()->SpawnActor<ABullet>(BulletTypes[i], GetTransform() + BulletCustomSpawnTransform[i], params);
					}
				}
			}
		}
	}
}