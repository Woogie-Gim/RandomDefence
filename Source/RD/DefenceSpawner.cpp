


#include "DefenceSpawner.h"
#include "DefenceEnemy.h"
#include "DefencePath.h"
#include "Components/SplineComponent.h"

// Sets default values
ADefenceSpawner::ADefenceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADefenceSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// 게임 시작 시 타이머 발동 (SpawnInterval 초마다 SpawnEnemy 함수 실행, 반복 true)
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ADefenceSpawner::SpawnEnemy, SpawnInterval, true);
}

void ADefenceSpawner::SpawnEnemy()
{
	// 다 뽑았으면 타이머 정지
	if (CurrentSpawnCount >= MaxSpawnCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	// 적 클래스와 경로가 설정되어 있는지 확인
	if (!EnemyClass || !TargetPath) return;

	// 스폰 위치 : 경로의 시작점 (0.0f)
	FVector SpawnLoc = TargetPath->SplineComponet->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);
	FRotator SpawnRot = TargetPath->SplineComponet->GetRotationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);

	// 소환
	ADefenceEnemy* NewEnemy = GetWorld()->SpawnActor<ADefenceEnemy>(EnemyClass, SpawnLoc, SpawnRot);

	if (NewEnemy)
	{
		// 길을 따라가게 명령
		NewEnemy->SetPath(TargetPath->SplineComponet);
		CurrentSpawnCount++;
	}
}

// Called every frame
void ADefenceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

