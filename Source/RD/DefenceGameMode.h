
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

	// 웨이브 시스템
	
	// 현재 웨이브
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWave = 1;

	// 웨이브 마다 스폰할 적 클래스들 (블루프린트에서 웨이브 적 유닛 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray<TSubclassOf<class ADefenceEnemy>> WaveEnemyClasses;

	// 게임 오버 시스템

	// 현재 맵에 살아 있는 적의 수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentEnemyCount = 0;

	// 적 유닛 제한
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 MaxEnemyLimit = 50;

	// 적 스폰 / 사망 시 카운트를 관리할 함수
	void AddEnemyCount();
	void RemoveEnemyCount();

	// 현재 웨이브의 남은 시간을 블루프린트로 보내주는 함수
	UFUNCTION(BlueprintPure, Category = "Wave")
	float GetWaveTimeRemaining() const;

protected:
	virtual void BeginPlay() override;

	// 1분 마다 호출될 웨이브 변경 함수
	void StartNextWave();

	// 타이머를 관리할 핸들
	FTimerHandle WaveTimerHandle;

	// 게임 오버 처리 함수
	void GameOver();

	// 패배 시 블루프린트에게 게임 오버 창을 띄우게 명령할 이벤트
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowGameOverUI();
};
