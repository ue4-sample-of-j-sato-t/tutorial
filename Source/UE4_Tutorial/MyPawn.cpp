// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// プレイヤー0に制御されるようにする
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// ルートコンポーネント生成
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// 表示用コンポーネント生成
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>("OurVisibleComponent");
	OurVisibleComponent->SetupAttachment(RootComponent);

	// カメラコンポーネント生成
	auto OurCameraComponent = CreateDefaultSubobject<UCameraComponent>("OurCamera");
	OurCameraComponent->SetupAttachment(RootComponent);
	// 位置・角度調整
	OurCameraComponent->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// スケール変更
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		CurrentScale += DeltaTime;
	}
	else
	{
		CurrentScale -= (DeltaTime * 0.5f);
	}
	// リミット
	CurrentScale = FMath::Clamp(CurrentScale, 1.f, 2.f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	// 移動
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.f) * 100.f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}

