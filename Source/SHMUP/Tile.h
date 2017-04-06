// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class SHMUP_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void NewTileOverlapBorder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void DestroyTileOverlapBorder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void Reposition();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	UStaticMeshComponent *TerrainMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UArrowComponent *FrontArrow = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UArrowComponent *BackArrow = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UBoxComponent *CreateNewTileTrigger = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	class UBoxComponent *DestroyCurrentTileTrigger = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Statistics")
	FVector MovementDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Statistics")
	float MovementSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Statistics")
	TArray<TSubclassOf<class ATile>> TileBlueprint;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
