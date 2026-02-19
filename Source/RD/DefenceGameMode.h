
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"

// 전방 선언
class ABaseUnit;

UCLASS()
class RD_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// 소환할 유닛들의 목록 (블루프린트에서 채워 넣을 예정)
	UPROPERTY(EditDefaultsOnly, Category = "Unit Spawning")
	TArray<TSubclassOf<ABaseUnit>> UnitPool;

	// 외부 (UI)에서 호출할 소환 함수
	UFUNCTION(BlueprintCallable, Category = "Unit Spawning")
	void SpawnRandomUnit();

	// 재화

	// 현재 내가 가진 골드 (초기 자본금 10원)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Economy")
	int32 CurrentGold = 10;

	// 유닛 1회 뽑기 비용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
	int32 SpawnCost = 3;

	// 골드 획득 함수 (적이 죽을 때 호출
	UFUNCTION(BlueprintCallable, Category = "Economy")
	void AddGold(int32 Amount);

	// 골드 지불 함수 (가챠 버튼 누를 때 호출)
	UFUNCTION(BlueprintCallable, Category = "Economy")
	bool SpendGold(int32 Amount);
};
