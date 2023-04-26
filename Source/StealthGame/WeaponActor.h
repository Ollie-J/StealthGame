// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class STEALTHGAME_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	class USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
		class UStaticMeshComponent* Attachment01;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		USceneComponent* Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bInCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		bool bIsGun;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
