


#include "DefenceEnemy.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"
#include "SEnemyHealthBar.h"
#include "DefenceGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADefenceEnemy::ADefenceEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // 이동을 위해 Tick = true

	// 컴포넌트 생성
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(RootComponent);

	// 위치 잡기 (머리 위)
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));

	// 3D 월드가 아니라 2D 화면 (Screen)에 그림 (최적화)
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	// 드로우 사이즈 (화면에 그려질 크기)
	HPBarWidget->SetDrawSize(FVector2D(80.0f, 10.0f));
}

// Called when the game starts or when spawned
void ADefenceEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 태어날 때 MaxHP
	CurrentHP = MaxHP;
	bIsDead = false;

	CurrentOpacity = 1.0f;

	// 메쉬에서 머터리얼을 가져와 '동적 머터리얼'로 만듦
	// 유닛 하나하나의 투명도를 따로 조절 가능
	UMaterialInterface* BaseMat = GetMesh()->GetMaterial(0); // 첫 번째 슬롯의 머터리얼 가져오기
	if (BaseMat)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMat, this);
		GetMesh()->SetMaterial(0, DynamicMaterial); // 만든 동적 머터리얼로 교체
	}

	// 게임 시작시, Slate 위젯을 생성해서 컴포넌트에 끼워 넣음
	if (HPBarWidget)
	{
		// 인자 넘겨주기
		HPBarWidget->SetSlateWidget(SNew(SEnemyHealthBar).OwnerEnemy(this));
	}
}

void ADefenceEnemy::SetPath(USplineComponent* NewSpline)
{
	PathSpline = NewSpline;
	CurrentDistance = 0.0f;	// 출발점으로 초기화
}

void ADefenceEnemy::OnTakeDamage(float DamageAmount)
{
	if (bIsDead) return; // 이미 죽었으면 return

	CurrentHP -= DamageAmount;

	// 체력이 0 이하면 사망 처리
	if (CurrentHP <= 0.0f)
	{
		CurrentHP = 0.0f;
		bIsDead = true;

		// 사망 로직

		// 현재 게임 모드를 가져와서 ADefenceGameMode로 Cast
		ADefenceGameMode* GM = Cast<ADefenceGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			// 골드 1원 획득
			GM->AddGold(1);
		}

		// 더 이상 공격받지 않게 충돌 끄기 (시체에 공격이 막히지 않게)
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// 더 이상 이동하지 못하게 컨트롤러 해제
		DetachFromControllerPendingDestroy();
		
		// 사망 애니메이션 재생
		float DeathAnimDuration = 2.0f; // 기본 2초
		if (DeathMontage)
		{
			// 몽타주를 재생하고 그 애니메이션의 길이를 바당옴
			DeathAnimDuration = PlayAnimMontage(DeathMontage);
		}
	}
}

// Called every frame
void ADefenceEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDead && PathSpline)
	{
		// 거리 갱신 (속도 * 시간) 만큼 앞으로 전진
		CurrentDistance += MoveSpeed * DeltaTime;

		// 전체 길이보다 더 갔다면? (한 바퀴 돎)
		float TotalLength = PathSpline->GetSplineLength();

		if (CurrentDistance >= TotalLength)
		{
			// 빙글빙글 돌게 하려면 0으로 초기화 (루프)
			CurrentDistance -= TotalLength;
		}

		// 해당 거리의 월드 좌표와 회전값 가져오기
		FVector NewLocation = PathSpline->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);
		FRotator NewRotation = PathSpline->GetRotationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);

		// 위치 적용
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}

	// 죽었을 때 투명도 처리 (Fade Out)
	if (bIsDead && DynamicMaterial)
	{
		// 투명도 값 감소 (시간에 비례해서)
		CurrentOpacity -= DeltaTime * FadeOutSpeed;

		// 머티리얼에 값 적용
		DynamicMaterial->SetScalarParameterValue(TEXT("OpacityParam"), CurrentOpacity);

		// 완전히 투명해지면 삭제
		if (CurrentOpacity <= 0.0f)
		{
			CurrentOpacity = 0.0f;
			Destroy();
		}
	}
}

// Called to bind functionality to input
void ADefenceEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

