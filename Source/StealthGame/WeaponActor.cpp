// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"
#include "StealthCharacter.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GUN"));
	RootComponent = Weapon;
	
	Attachment01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attachment"));
	Attachment01->SetupAttachment(Weapon);
	bIsGun = true;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(Weapon);
	Muzzle->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	bInCombat = false;
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

