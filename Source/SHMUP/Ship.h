// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

UCLASS()
class SHMUP_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Statistics")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Statistics")
	float MaxLateralSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Statistics")
	float MaxForwardSpeed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	UStaticMeshComponent *CoreMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UArrowComponent *DirectionArrow = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Components")
	UCameraComponent *Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Weapon")
	TArray<class AWeaponActor *> MainWeaponSubsystem;

	UFUNCTION(BlueprintCallable, category = "Damage")
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

private:
	FVector Forward, Right;

	void ParseChildActors();

	void SetPlayerShip();

	void IgnoreCollisionWithChildActors();

	bool PlayerShip = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, category = "Movement")
	virtual void MoveForward(float Intensity);

	UFUNCTION(BlueprintCallable, category = "Movement")
	virtual void MoveRight(float Intensity);
	
	UFUNCTION(BlueprintCallable, category = "Weapon")
	virtual void Fire();
};
