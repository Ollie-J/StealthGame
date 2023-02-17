// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Door.h"
#include "UObject/UObjectBase.h"
#include "StealthCharacter.generated.h"

UCLASS()
class STEALTHGAME_API AStealthCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:
	
	AStealthCharacter();

	//Third Person Camera //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCameraComponent* TPCamera;

	// Character Movement //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Movement")
		float Speed;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Movement")
		float TurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Movement")
		float LookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Movement")
		float SprintSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Night Vision")
		struct FPostProcessSettings NVS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Night Vision")
		bool bNVOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracer")
		float LineTraceCamera = 750.f;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// Player Movement //
	void MoveF(float Value);
	void MoveR(float Value);
	void CanCrouch();
	void Sprinting();
	void StopSprinting();
	void Jumping();
	void NoJump();
	void OnAction();

	//CAMERA FUNCTIONS//
	
	void CamHoriRotation(float Rate);
	void CamVertRotation(float Value);

	
	//NIGHT VISION//
	void NightVision();
	void NightVisionOn();
	void NightVisionOff();

	
	

};