// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GUN"));
	Weapon->SetupAttachment(RootComponent);
	RootComponent = Weapon;

	Attachment01 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Attachment"));
	Attachment01->SetupAttachment(Weapon);

	//Attachment02 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Attachment"));
	//Attachment02->SetupAttachment(Weapon);
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

