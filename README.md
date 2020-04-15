# tutorial
チュートリアルを一通り行う

## コンポーネントを持つアクタの作成

1. メンバ変数に持たせたいコンポーネント型のポインタを持たせる
1. コンストラクタでコンポーネントを生成する
1. 初期設定を行う

1：クラス宣言
```cpp
	// StaticMeshを持たせる
	UPROPERTY(VisibleAnywhere)	// エディタ上で編集できるようにするために VisibleAnywhere を付ける
	UStaticMeshComponent* VisualMesh;
```

2~3：クラス実装
```cpp
	// コンポーネントを生成して保持
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// アクタにセット
	VisualMesh->SetupAttachment(RootComponent);

	// ----- 以下は初期設定
	// デフォルトのメッシュをセット
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_cube.Shape_cube"));
	if (CubeVisualAsset.Succeeded())	// ロードできたか
	{
		// ロードしたメッシュをコンポーネントにセット
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
	}
	// アクタの原点からの相対位置
	VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
```

## カメラ切り替え

1. 切り替えを行いたいカメラを配置する
1. それらを保持する
1. 切り替えたいタイミングでプレイヤーコントローラーにセットする

2：保持するメンバを追加
```cpp
	// アクタ型で保持する
	// ここでは不特定数として配列にしている
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Cameras;
```
3：切り替え処理
```cpp
// プレイヤーコントローラー取得のために追加のインクルードが必要
#include "Kismet/GameplayStatics.h"

	/* 中略 */

	// プレイヤーコントローラー取得
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	// （何度も配列にアクセスするのは面倒なので変数化）
	// ※nullチェックは省略
	auto TargetCamera = Cameras[NowCameraIndex];

	// 瞬時に切り替える
	OurPlayerController->SetViewTarget(TargetCamera);

	// スムース（移動+回転）で切り替える
	OurPlayerController->SetViewTargetWithBlend(TargetCamera, SmoothBlendTime);
```
