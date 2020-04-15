// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChange = 2.0f;
	const float SmoothBlendTime = 0.75f;
	
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChange;

		// プレイヤーコントローラー取得
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController) // 取得できたか
		{
			// 次のカメラを指定
			int32 BeforCameraIndex = NowCameraIndex;
			NowCameraIndex = (NowCameraIndex + 1) % Cameras.Num();

			// 切り替え先がある
			if ((NowCameraIndex != BeforCameraIndex) && (Cameras[NowCameraIndex] != nullptr))
			{
				// 変数に保持
				auto TargetCamera = Cameras[NowCameraIndex];

				// インデックスが奇数のときは瞬時
				if (NowCameraIndex % 2)
				{
					OurPlayerController->SetViewTarget(TargetCamera);
				}
				else  // 偶数ならスムース
				{
					OurPlayerController->SetViewTargetWithBlend(TargetCamera, SmoothBlendTime);
				}
			}
		}
	}
}

