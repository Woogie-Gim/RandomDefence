

#include "DefenceGameMode.h"
#include "BaseUnit.h"

void ADefenceGameMode::SpawnRandomUnit()
{
	// 목록이 비어 있다면 아무것도 안 함
	if (UnitPool.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("유닛 풀이 비어 있습니다!"));
		return;
	}

	// 랜덤 뽑기 (0 ~ 목록 개수 - 1 사이의 랜덤 숫자)
	int32 RandomIndex = FMath::RandRange(0, UnitPool.Num() - 1);

	// 당첨된 유닛 클래스 가져오기
	TSubclassOf<ABaseUnit> SelectedUnitClass = UnitPool[RandomIndex];

	if (SelectedUnitClass)
	{
		// 기본 소환 위치
		FVector BaseLocation = FVector(0.0f, 0.0f, 50.0f);

		// 약간의 랜덤 오프셋 (중앙을 기준으로 가로세로 -150 ~ 150 범위 내에 흩뿌림)
		float RandomX = FMath::RandRange(-150.0f, 150.0f);
		float RandomY = FMath::RandRange(-150.0f, 150.0f);
		FVector SpawnLocation = BaseLocation + FVector(RandomX, RandomY, 0.0f);

		FRotator SpawnRotation = FRotator::ZeroRotator;

		// 스폰 파라미터 설정 겹치면 옆으로 밀어서 소환
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 소환 SpawnParams를 마지막에 추가
		GetWorld()->SpawnActor<ABaseUnit>(SelectedUnitClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}
