#include "AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



AAICharacter::AAICharacter()
{
 
	PrimaryActorTick.bCanEverTick = true;

	DefaultSpeed = 200.0f;
	PatrolSpeed = 150.0f;
	ChaseSpeed = 600.0f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}



void AAICharacter::UpdateWalkSpeed(float NewWalkSpeed)
{
	ChaseSpeed = NewWalkSpeed;
}
