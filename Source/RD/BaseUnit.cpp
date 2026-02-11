

#include "BaseUnit.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h" // 적들을 찾기 위해 추가
#include "Projectile.h"				// 투사체를 인지하기 위해 추가

// Sets default values
ABaseUnit::ABaseUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 데칼 컴포넌트 생성 및 설정
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	// 안보이는 기본 상태
	SelectionDecal->SetVisibility(false);

	// 데칼 -90도 회전
	SelectionDecal->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SelectionDecal->DecalSize = FVector(128.0f, 128.0f, 128.0f);

	// AutoProssesAI 기본 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
	AttackTimer = 0.0f;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 타겟 유효성 검사
	if (CurrentTarget)
	{
		// 타겟이 없거나 죽었거나 너무 멀어지면 새로운 타겟 찾기
		if (CurrentTarget->bIsDead || GetDistanceTo(CurrentTarget) > AttackRange)
		{
			CurrentTarget = nullptr; // 타겟 해제
		}
	}

	// 타겟이 없으면 찾기
	if (!CurrentTarget)
	{
		FindTarget();
	}

	// 타겟이 있으면 공격 및 회전
	if (CurrentTarget)
	{
		// 회전 (Z축 고정)
		FVector Direction = CurrentTarget->GetActorLocation() - GetActorLocation();
		FRotator LookRot = Direction.Rotation();
		SetActorRotation(FRotator(0.0f, LookRot.Yaw, 0.0f));

		// 공격 타이머
		AttackTimer += DeltaTime;
		if (AttackTimer >= AttackSpeed)
		{
			Attack();
			AttackTimer = 0.0f;
		}
	}
}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnit::SetSelectionState(bool bIsSelected)
{
	if (SelectionDecal)
	{
		SelectionDecal->SetVisibility(bIsSelected);
	}
}

void ABaseUnit::FindTarget()
{
	// 범위 (Sphere) 안에 겹친 모든 Actor 가져오기
	TArray<AActor*> FoundEnemies;

	// 맵에 있는 모든 적(DefenceEnemy)을 찾습니다.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefenceEnemy::StaticClass(), FoundEnemies);

	float ShortestDistance = AttackRange;
	ADefenceEnemy* NearestEnemy = nullptr;

	// 가장 가까운 적 찾기 알고리즘
	for (AActor* Actor : FoundEnemies)
	{
		ADefenceEnemy* Enemy = Cast<ADefenceEnemy>(Actor);
		if (Enemy && !Enemy->bIsDead)
		{
			// 나와 적 사이의 거리 계산
			float Dist = GetDistanceTo(Enemy);

			// 사거리 안이고 기존 찾은 유닛보다 가까우면 갱신
			if (Dist <= AttackRange && Dist < ShortestDistance)
			{
				ShortestDistance = Dist;
				NearestEnemy = Enemy;
			}
		}
	}

	CurrentTarget = NearestEnemy;
}

void ABaseUnit::Attack()
{
	// 타겟도 있고 투사체 클래스도 설정 되어 있어야 함
	if (CurrentTarget && ProjectileClass)
	{
		// 공격 애니메이션 재생, 몽타주가 설정 되어 있다면 재생
		if (AttackMontage)
		{
			PlayAnimMontage(AttackMontage);
		}

		// 발사 위치 (내 위치)와 회전 (적을 바라보는 방향)
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = (CurrentTarget->GetActorLocation() - SpawnLocation).Rotation();

		// 소환 파라미터
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// 투사체 진짜로 소환
		AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		// 투사체에게 정보(타겟, 데미지) 전달
		if (SpawnedProjectile)
		{
			SpawnedProjectile->Initialize(CurrentTarget, AttackDamage);
		}
	}
}
