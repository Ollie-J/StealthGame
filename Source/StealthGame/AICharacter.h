// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class STEALTHGAME_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAICharacter();

	//void WhenHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

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


protected:
		
		
public:

	UFUNCTION(BlueprintCallable)
		void UpdateWalkSpeed(float NewWalkSpeed);


};
