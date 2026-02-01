

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

	// 소환 위치 설정 (맵 중앙 0, 0, 100에 소환)
	FVector SpawnLocation = FVector(0.0f, 0.0f, 100.0f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// 소환
	if (SelectedUnitClass)
	{
		GetWorld()->SpawnActor<ABaseUnit>(SelectedUnitClass, SpawnLocation, SpawnRotation);
		
		// UE_LOG(LogTemp, Log, TEXT("랜덤 유닛 소환 완료!"));
	}
}
