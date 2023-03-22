// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API UCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCharAnimInstance();

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Anim")
	void UUpdateAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jumping")
		bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jumping")
		bool bisAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		bool isCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jumping")
		bool bInCombat;
};
