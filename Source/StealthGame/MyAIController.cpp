// Fill out your copyright notice in the Description page of Project Settings.
#include "MyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	//GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPawnDetection);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	HasSight = "bHasSight";
	AIActor = "EnemyActor";
	Time = 4.0f;
	HasSightTimer = 4.0f;
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


	TSubclassOf<UAISense> Sense;
	GetPerceptionComponent()->GetCurrentlyPerceivedActors(Sense, this->PActor);
	int32 PerNum = this->PActor.Num();
	bool FoundPlayer = false;
	//UE_LOG(LogTemp, Warning, TEXT("%i"), PerNum);
	for (int i = 0; i < PerNum; i++)
	{
		AActor* Actor = this->PActor[i];
		if (Actor->ActorHasTag(FName(TEXT("Player"))))
		{
			FoundPlayer = true;
			UE_LOG(LogTemp, Warning, TEXT(" Player found"));
			GetBlackboardComponent()->SetValueAsBool(FName(HasSight), true);
			GetBlackboardComponent()->SetValueAsObject(FName(AIActor), Actor);

			AAICharacter* AI = Cast<AAICharacter>(GetPawn());
			if (FoundPlayer) {
				AI->UpdateWalkSpeed(600.0f);
			}
			
			
		}
	}
	this->PActor.Reset(PerNum);

	if (!FoundPlayer)
	{
		GetBlackboardComponent()->SetValueAsBool(FName(HasSight), false);
	}
}

FRotator AMyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) 
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}


	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

