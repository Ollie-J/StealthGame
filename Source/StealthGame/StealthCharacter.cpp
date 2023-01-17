#include "StealthCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"



// Sets default values
AStealthCharacter::AStealthCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	
	//PlayerMesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	//Camera Arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 500.f;

	//Camera
	TPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third-Person-Camera"));
	TPCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	TPCamera->bUsePawnControlRotation = false;
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
	InputComponent->BindAxis("MoveForward", this, &AStealthCharacter::MoveForward);
	InputComponent->BindAxis("MoveForward", this, &AStealthCharacter::Turn);
}

void AStealthCharacter::MoveForward(float InputAxis)
{
	AddMovementInput(GetActorForwardVector(), InputAxis);
}

void AStealthCharacter::Turn(float InputAxis)
{
	TurnAmount = InputAxis;
	AddActorLocalRotation(FRotator(0.0f, TurnAmount, 0.0f));
}

