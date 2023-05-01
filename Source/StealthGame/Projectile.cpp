// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "StealthCharacter.h"

//#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	SphereCollision->InitSphereRadius(15.0f);
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollision);
	
	RootComponent = SphereCollision;
	

	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjMoveComp->SetUpdatedComponent(SphereCollision);
	ProjMoveComp->InitialSpeed = 3000.0f;
	ProjMoveComp->MaxSpeed = 3000.0f;
	ProjMoveComp->bRotationFollowsVelocity = true;
	ProjMoveComp->ProjectileGravityScale = 0.0f;

	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Assets/Bullet.Bullet'"));
		
	if (Mesh.Succeeded()) {
		ProjMesh->SetStaticMesh(Mesh.Object);
	}
	ProjMesh->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	
	

	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireDirec(const FVector& ShootDirec)
{
	ProjMoveComp->Velocity = ShootDirec * ProjMoveComp->InitialSpeed;
}





