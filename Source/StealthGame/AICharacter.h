// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class STEALTHGAME_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float DefaultSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float ChaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float PatrolSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rifle")
		USkeletalMeshComponent* Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionComp")
		UBoxComponent* BCollision;

protected:
		//virtual void BeginPlay() override;
		
public:

	UFUNCTION(BlueprintCallable)
		void UpdateWalkSpeed(float NewWalkSpeed);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _DamageAmount);

};
