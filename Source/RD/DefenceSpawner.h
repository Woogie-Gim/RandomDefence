

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenceSpawner.generated.h"

class ADefenceEnemy;
class ADefencePath;

UCLASS()
class RD_API ADefenceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenceSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 스폰 타이머 함수
	void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 소환할 적 종류
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<ADefenceEnemy> EnemyClass;

	// 적이 따라갈 길 (레벨에 배치된 것과 연결)
	UPROPERTY(EditAnywhere, Category = "Spawing")
	TObjectPtr<ADefencePath> TargetPath;

	// 2초마다 소환
	UPROPERTY(EditAnywhere, Category = "Spawing")
	float SpawnInterval = 2.0f;

	// 총 소환 마리
	UPROPERTY(EditAnywhere, Category = "Spawing")
	int32 MaxSpawnCount = 10;

private:
	// 현재 유닛 수
	int32 CurrentSpawnCount = 0;
	// 타이머 관리자
	FTimerHandle SpawnTimerHandle;
};
