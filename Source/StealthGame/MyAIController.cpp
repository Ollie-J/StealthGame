// Fill out your copyright notice in the Description page of Project Settings.
#include "MyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AMyAIController::AMyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AISightAngle;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetection);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMyAIController::OnPossess(APawn* MyPawn)
{
	Super::OnPossess(MyPawn);

	RunBehaviorTree(BTree1);
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AMyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) 
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}


	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AMyAIController::OnPawnDetection(const TArray<AActor*> &DetectedPawns)
{

}