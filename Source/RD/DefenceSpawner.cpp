


#include "DefenceSpawner.h"
#include "DefenceEnemy.h"
#include "DefencePath.h"
#include "DefenceGameMode.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

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

	// 경로가 설정되어 있는지 확인 (EnemyClass 확인은 아래에서 통합 처리)
	if (!TargetPath) return;

	// 스폰 위치 : 경로의 시작점 (0.0f)
	FVector SpawnLoc = TargetPath->SplineComponet->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);
	FRotator SpawnRot = TargetPath->SplineComponet->GetRotationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World);

	// 게임모드 가져오기
	ADefenceGameMode* GM = Cast<ADefenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	// 소환할 클래스 변수 (기본값은 스포너에 세팅된 EnemyClass)
	TSubclassOf<ADefenceEnemy> ClassToSpawn = EnemyClass;

	// 게임모드가 있고, 웨이브 배열에 값이 있다면 웨이브 클래스로 덮어쓰기!
	if (GM && GM->WaveEnemyClasses.Num() > 0)
	{
		int32 ClassIndex = FMath::Clamp(GM->CurrentWave - 1, 0, GM->WaveEnemyClasses.Num() - 1);
		ClassToSpawn = GM->WaveEnemyClasses[ClassIndex];
	}

	// 최종적으로 소환할 클래스가 비어있으면 중단
	if (!ClassToSpawn) return;

	// 스폰 실행
	ADefenceEnemy* NewEnemy = GetWorld()->SpawnActor<ADefenceEnemy>(ClassToSpawn, SpawnLoc, SpawnRot);

	// 스폰에 성공했다면 각종 세팅 적용
	if (NewEnemy)
	{
		// 1. 길을 따라가게 명령
		NewEnemy->SetPath(TargetPath->SplineComponet);

		// 2. 스포너 내부 생성 카운트 증가
		CurrentSpawnCount++;

		// 3. 게임모드의 전체 유닛 카운트 증가
		if (GM)
		{
			GM->AddEnemyCount();
		}
	}
}

// Called every frame
void ADefenceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

