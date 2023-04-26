// Fill out your copyright notice in the Description page of Project Settings.


#include "CharAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponActor.h"
#include "StealthCharacter.h"


UCharAnimInstance::UCharAnimInstance()
{

}

void UCharAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr) 
	{
		Pawn = TryGetPawnOwner();
	}
}

void UCharAnimInstance::UUpdateAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn) {

		bIsFalling = Pawn->GetMovementComponent()->IsFalling();
		isCrouching = Pawn->GetMovementComponent()->IsCrouching();
		//AIMING TODO
		//SHOOTING TODO
		FVector Speed = Pawn->GetVelocity();
		FVector lateralSpeed = FVector(Speed.X, Speed.Y, 0.0f); // Z for jump
		MovementSpeed = lateralSpeed.Size();

		
	}
}

