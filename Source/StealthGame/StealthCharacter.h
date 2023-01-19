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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float TurnRate;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveF(float InputAxis);

	void MoveR(float Value);

	void CamHoriRotation(float Rate);

	

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
		class UCameraComponent* TPCamera;
	*/
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float Speed;

};