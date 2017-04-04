// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TerrainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerrainMesh"));
	SetRootComponent(TerrainMesh);

	FrontArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontArrow"));
	FrontArrow->SetVisibility(true);
	FrontArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BackArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BackArrow"));
	BackArrow->SetVisibility(true);
	BackArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CreateNewTileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CreateNewTileTrigger"));
	CreateNewTileTrigger->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DestroyCurrentTileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyCurrentTileTrigger"));
	DestroyCurrentTileTrigger->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CreateNewTileTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::NewTileOverlapBorder);
	DestroyCurrentTileTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::DestroyTileOverlapBorder);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	MovementDirection = -GetActorForwardVector();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(DeltaTime * MovementSpeed * MovementDirection);
}


void ATile::NewTileOverlapBorder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("MapBorder"))
	{
		int32 Len = TileBlueprint.Num();
		if (Len >= 0)
		{
			int32 Index = FMath::RandRange(0, Len - 1);
			ATile *NewTile = GetWorld()->SpawnActor<ATile>(TileBlueprint[Index], FrontArrow->GetComponentLocation(), FrontArrow->GetComponentRotation());
			NewTile->Reposition();
		}
	}
}

void ATile::DestroyTileOverlapBorder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("MapBorder"))
	{
		this->Destroy();
	}
}


void ATile::Reposition()
{
	FVector CurrentLocation, Offset;
	CurrentLocation = GetActorLocation();
	Offset = BackArrow->GetComponentLocation();
	AddActorLocalOffset(CurrentLocation - Offset);
}