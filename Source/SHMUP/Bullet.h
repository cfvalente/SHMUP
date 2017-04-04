// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHMUP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Statistics")
	float MaxForwardSpeed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	UStaticMeshComponent *BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UArrowComponent *DirectionArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UParticleSystemComponent *Particles;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void Fire();

private:
	FVector Forward;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
