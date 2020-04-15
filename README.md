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