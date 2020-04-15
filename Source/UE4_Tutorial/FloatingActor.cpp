// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 基礎メッシュ
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_cube.Shape_cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// パーティクル
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->bAutoActivate = false;
	//ParticleSystem->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if( ParticleAsset.Succeeded()){
		ParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotator = GetActorRotation();

	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	NewLocation.Z += DeltaHeight * FloatSpeed;

	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotator.Yaw += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotator);

	ParticleSystem->SetRelativeLocation(ParticlePosition);
}

void AFloatingActor::ToggleActive()
{
	ParticleSystem->ToggleActive();
}

