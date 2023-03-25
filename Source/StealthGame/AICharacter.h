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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float DefaultSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float ChaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AIMovementSpeed", meta = (ExposeOnSpawn = "true"))
		float PatrolSpeed;

protected:

		
public:

	UFUNCTION(BlueprintCallable)
		void UpdateWalkSpeed(float NewWalkSpeed);

};
