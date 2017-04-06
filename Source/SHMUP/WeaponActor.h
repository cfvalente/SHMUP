// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SHMUP_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	UStaticMeshComponent *CoreMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UArrowComponent *DirectionArrow = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	TArray<TSubclassOf<class ABullet>> BulletTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	TArray<FTransform> BulletCustomSpawnTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float FiringCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	bool UseMuzzleLocation = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Weapon")
	float LastShotTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	FTransform MuzzleTransform;

public:	
	virtual void Fire();
	
	
};
