


#include "DefenceEnemy.h"
#include "Components/SplineComponent.h"

// Sets default values
ADefenceEnemy::ADefenceEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // 이동을 위해 Tick = true

}

// Called when the game starts or when spawned
void ADefenceEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 태어날 때 MaxHP
	CurrentHP = MaxHP;
	bIsDead = false;
}

void ADefenceEnemy::SetPath(USplineComponent* NewSpline)
{
	PathSpline = NewSpline;
	CurrentDistance = 0.0f;	// 출발점으로 초기화
}

void ADefenceEnemy::OntakeDamage(float DamageAmount)
{
	if (bIsDead) return; // 이미 죽었으면 return

	CurrentHP -= DamageAmount;

	// 체력이 0 이하면 사망 처리
	if (CurrentHP <= 0.0f)
	{
		CurrentHP = 0.0f;
		bIsDead = true;

		// 사망 로직

		// 더 이상 이동하지 못하게 컨트롤러 해제
		DetachFromControllerPendingDestroy();

		// 충돌체 끄기 (시체에 공격이 막히지 않게)
	}
}

// Called every frame
void ADefenceEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PathSpline)
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
}

// Called to bind functionality to input
void ADefenceEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

