// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat) {
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void ADoor::OnInteract() 
{
	UE_LOG(LogTemp, Display, TEXT("INTERACTED WITH THE DOOR"));

	if (bIsDoorClosed) {
		Timeline.Play(); //opens the door
	}
	else
	{
		Timeline.Reverse(); //closes the door
	}
	bIsDoorClosed = !bIsDoorClosed; //flip flop
}

void ADoor::OpenDoor(float Value) 
{
	FRotator Rot = FRotator(0.0f, DoorRotateAngle * Value, 0.0f);

	DoorMesh->SetRelativeRotation(Rot);
}