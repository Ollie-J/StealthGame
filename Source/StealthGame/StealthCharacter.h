// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthCharacter.generated.h"

UCLASS()
class STEALTHGAME_API AStealthCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:
	// Sets default values for this character's properties
	AStealthCharacter();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCameraComponent* TPCamera;

	/*DELTE THE STATIC MESH AS THE BP ALREADY HAS A SKELETAL MESH*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		UStaticMeshComponent* StaticMesh;

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


	void CamHoriRotation(float Rate);

	void CamVertRotation(float Value);

	

	void NightVision();

	void NormalVision();

	void NightVisionOn();

	void NightVisionOff();

	
	

};