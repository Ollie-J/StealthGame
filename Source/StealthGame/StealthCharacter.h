#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharAnimInstance.h"
#include "Components/SpotLightComponent.h"
#include "Door.h"
#include "Projectile.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "UObject/UObjectBase.h"
#include "StealthCharacter.generated.h"

UCLASS()
class STEALTHGAME_API AStealthCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:
	AStealthCharacter();

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		class USpotLightComponent* LaserPointer;
	*/
	UPROPERTY(EditAnywhere, Category = "SoundCue")
		USoundCue* PistolSoundCue;
	UPROPERTY(EditAnywhere, Category = "AudioComp")
		UAudioComponent* PistolAudioComp;

	UPROPERTY(EditAnywhere, Category = "Proj")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pistol")
		USkeletalMeshComponent* Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muzzle")
		FVector Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpotLight")
		class USpotLightComponent* Flashlight;

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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aiming")
		bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "aiming")
		bool bIsFlashLightOn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float PlayerMaxHealth;

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

	//Weapon
	void Aiming();
	void StopAiming();

	UFUNCTION()
	void Fire();
	

	//Flashlight
	void FlashLight();
	void FlashLightOn();
	void FlashLightOff();

	
};