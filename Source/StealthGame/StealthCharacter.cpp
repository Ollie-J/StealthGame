#include "StealthCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AStealthCharacter::AStealthCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	Speed = 0.0f;
	TurnRate = 45.0f;
	
	//PlayerMesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	/*
	//Camera Arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 500.f;
	CameraArm->bUsePawnControlRotation = true;

	//Camera
	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third-Person-Camera"));
	TPCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	//TPCamera->bUsePawnControlRotation = false;
	*/
	
	
}

// Called when the game starts or when spawned
void AStealthCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	PlayerInputComponent->BindAxis("MoveForward", this, &AStealthCharacter::MoveF);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStealthCharacter::MoveR);
	
	//Rotation
	PlayerInputComponent->BindAxis("Turn", this, &AStealthCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnAxis", this, &AStealthCharacter::CamHoriRotation);
}

void AStealthCharacter::MoveF(float InputAxis)
{
	if (InputAxis != 0)
	{
		AddMovementInput(GetActorForwardVector(), InputAxis);
	}
}

void AStealthCharacter::MoveR(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AStealthCharacter::CamHoriRotation(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

