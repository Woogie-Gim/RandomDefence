
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
};
