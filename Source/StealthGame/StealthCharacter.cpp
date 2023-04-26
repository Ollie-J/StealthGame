#include "StealthCharacter.h"
#include "Engine/Scene.h"
#include "Math/Color.h"
#include "UObject/UObjectBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h" 
#include "CharAnimInstance.h"
#include "Door.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

AStealthCharacter::AStealthCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bNVOn = false;
	Speed = 300.0f;
	SprintSpeedMultiplier = 2.0f;
	TurnRate = 45.0f;
	LookUpRate = 45.0f;
	bIsAiming = false;

	// SETTING PROPERTIES WITHIN THE CHAR MOVEMENT // 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.0f;
	GetCharacterMovement()->CrouchedHalfHeight = 20.0f;
	GetCharacterMovement()->bCanWalkOffLedges = true;
	//GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;

	//Camera Arm TP
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 300.f;
	CameraArm->TargetOffset = FVector(0.f, 0.0f, 100.f);
	CameraArm->bUsePawnControlRotation = true;

	//Camera Third Person
	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third-Person-Camera"));
	TPCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	TPCamera->bUsePawnControlRotation = false;

	Pistol = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pistol"));
	Pistol->SetupAttachment(RootComponent);
	Pistol->CastShadow = false;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Pistol);
	
	LaserPointer = CreateDefaultSubobject<USpotLightComponent>(TEXT("Laser"));
	LaserPointer->Intensity = 100000.0f;
	LaserPointer->AttenuationRadius = 1205.676636f;
	LaserPointer->InnerConeAngle = 0.5f;
	LaserPointer->OuterConeAngle = 0.5f;
	LaserPointer->SourceRadius = 0.0f;
	LaserPointer->SoftSourceRadius = 0.0f;
	LaserPointer->SourceLength = 1.0f;
	//LaserPointer->SetupAttachment(Pistol);

	
	
	

}

// Called when the game starts or when spawned
void AStealthCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Pistol->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("PistolSocket"));
	
}

// Called every frame
void AStealthCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStealthCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Events
		//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AStealthCharacter::MoveF);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStealthCharacter::MoveR);
	
	//Camera Rotation
	PlayerInputComponent->BindAxis("RotationH", this, &AStealthCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnAxis", this, &AStealthCharacter::CamHoriRotation);
	PlayerInputComponent->BindAxis("RotationV", this, &AStealthCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("RotationV", this, &AStealthCharacter::CamVertRotation);

	//Action Events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AStealthCharacter::Jumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AStealthCharacter::NoJump);
	PlayerInputComponent->BindAction("NVOn", IE_Pressed, this, &AStealthCharacter::NightVision);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AStealthCharacter::CanCrouch);
	PlayerInputComponent->BindAction("Sprinting", IE_Pressed, this, &AStealthCharacter::Sprinting);
	PlayerInputComponent->BindAction("Sprinting", IE_Released, this, &AStealthCharacter::StopSprinting);
	PlayerInputComponent->BindAction("OpeningDoor", IE_Pressed, this, &AStealthCharacter::OnAction);
	
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStealthCharacter::Aiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStealthCharacter::StopAiming);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStealthCharacter::Fire);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AStealthCharacter::StopFire);
}

void AStealthCharacter::MoveF(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AStealthCharacter::MoveR(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}



void AStealthCharacter::CamHoriRotation(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AStealthCharacter::CamVertRotation(float Value)
{
	if (Value)
	{
		float temp = CameraArm->GetRelativeRotation().Pitch + Value;
		if (temp < 25 && temp > -65)
		{
			CameraArm->AddLocalRotation(FRotator(Value, 0, 0));
		}
	
	}
}

void AStealthCharacter::Jumping()
{
	Jump();
	
}

void AStealthCharacter::NoJump()
{
	StopJumping();
}

void AStealthCharacter::NightVision()
{
	
	if (bNVOn) {
		NightVisionOff();
	}
	else
	{
		NightVisionOn();
	}
}

void AStealthCharacter::NightVisionOn()
{
	bNVOn = true;
	NVS.bOverride_BloomIntensity = true;
	NVS.BloomIntensity = 20.0f; //set to 20
	NVS.VignetteIntensity = 1.0f; //set to 1
	NVS.AutoExposureBias = 3.0f;
	static const FLinearColor NVC = FLinearColor(0.0f, 255.0f, 0.0f);
	NVS.bOverride_LensFlareTint = false;
	//NVS.LensFlareTint = NVC;
	NVS.bOverride_ColorGamma = true;
	TPCamera->PostProcessSettings = NVS;
	return;
}

void AStealthCharacter::NightVisionOff()
{
	bNVOn = false;
	NVS.bOverride_BloomIntensity = true;
	NVS.BloomIntensity = 0.0f;
	NVS.VignetteIntensity = 0.0f;
	NVS.AutoExposureBias = 0.5f;
	NVS.bOverride_ColorGamma = false;
	TPCamera->PostProcessSettings = NVS;
	return;
}



void AStealthCharacter::CanCrouch()
{
	if (bIsCrouched) {
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AStealthCharacter::Sprinting()
{

	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void AStealthCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

void AStealthCharacter::OnAction()
{
	if (TPCamera == nullptr) return;

	FHitResult HitResult;
	FVector Start = TPCamera->GetComponentLocation();
	FVector End = Start + TPCamera->GetForwardVector() * LineTraceCamera;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);

	ADoor* Door = Cast<ADoor>(HitResult.GetActor());
	if (Door) {
		Door->OnInteract();
	}
}
	
void AStealthCharacter::Aiming() {

	if (!GetMesh()) return;
	UCharAnimInstance* Combat = Cast<UCharAnimInstance>(GetMesh()->GetAnimInstance());
	if (!Combat) return;
	Combat->bInCombat = true;
	GetMovementComponent()->CanEverCrouch();

}

void AStealthCharacter::StopAiming() {
	if (!GetMesh()) return;
	UCharAnimInstance* Combat = Cast<UCharAnimInstance>(GetMesh()->GetAnimInstance());
	if (!Combat) return;
	Combat->bInCombat = false;
}

void AStealthCharacter::Fire() {
	if (!GetMesh()) return;
	UCharAnimInstance* FireAnim = Cast<UCharAnimInstance>(GetMesh()->GetAnimInstance());
	if (!FireAnim) return;
	FireAnim->bisAttack = true;
}

void AStealthCharacter::StopFire() {
	if (!GetMesh()) return;
	UCharAnimInstance* FireAnim = Cast<UCharAnimInstance>(GetMesh()->GetAnimInstance());
	if (!FireAnim) return;
	FireAnim->bisAttack = false;
}