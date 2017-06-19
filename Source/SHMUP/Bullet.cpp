// Fill out your copyright notice in the Description page of Project Settings.

#include "SHMUP.h"
#include "Ship.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BulletMesh->SetCollisionProfileName("OverlapAllDynamic");
	SetRootComponent(BulletMesh);
	
	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Forward = GetActorForwardVector();
	Owner = GetOwner();
	if (Owner != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Parent's Name: %s"), *GetOwner()->GetFName().ToString());
		if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn() == Owner)
		{
			PlayerBullet = true;
			//UE_LOG(LogTemp, Warning, TEXT("Ok!"));
		}
	}
}



// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Forward * DeltaTime * MaxForwardSpeed, true);
}


void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Owner != nullptr && Owner != OtherActor)
	{
		AShip *Ship;
		Ship = Cast<AShip>(OtherActor);
		if (Ship != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("OtherActor's Name: %s"), *OtherActor->GetFName().ToString());
			UGameplayStatics::ApplyDamage(Ship, Damage, nullptr, this, UDamageType::StaticClass());
			Destroy();
		}
	}
}
