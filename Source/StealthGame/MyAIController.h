// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class STEALTHGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()



public:
	AMyAIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviourTree")
		class UBehaviorTree* BTree1;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "BehaviourTree")
		class UBlackBoardComponent* BlackBoardComp;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightRadius = 50.0f;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAge = 3.0f;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AILoseSightRadius = AISightRadius + 10.0f;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAngle = 20.0f;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UAISenseConfig_Sight* SightConfig;

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void OnPossess(APawn* MyPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	 virtual FRotator GetControlRotation() const override;

	UFUNCTION()
		void OnPawnDetection(const TArray<AActor*> &DetectedPawns);
};
