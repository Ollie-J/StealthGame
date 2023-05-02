#include "AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"



AAICharacter::AAICharacter()
{
 
	PrimaryActorTick.bCanEverTick = true;

	DefaultSpeed = 200.0f;
	PatrolSpeed = 150.0f;
	ChaseSpeed = 600.0f;
	Health = 100.0f;
	MaxHealth = Health;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	
	
	//Creating Rifle and attaching to Socket Created in the game Engine
	Rifle = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pistol"));
	Rifle->SetupAttachment(RootComponent);
	Rifle->CastShadow = false;
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("WeaponSocket"));


	
	
}


void AAICharacter::UpdateWalkSpeed(float NewWalkSpeed)
{
	ChaseSpeed = NewWalkSpeed;
}


