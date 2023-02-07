// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Door.generated.h"

UCLASS()
class STEALTHGAME_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorFrame")
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorMesh")
		UStaticMeshComponent* DoorMesh;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimeline Timeline;
	bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurveFloat")
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorRotation")
		float DoorRotateAngle = 90.0f;

	UFUNCTION()
		void OpenDoor(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnInteract();

};
