
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "DefenceEnemy.h"
#include "BaseUnit.generated.h"

// 전방 선언
class UDecalComponent; 

UCLASS()
class RD_API ABaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 유니 선택 / 해제 함수 (Controller에서 호출)
	void SetSelectionState(bool bIsSelected);

	// 현재 타겟 (내가 보고 있는 적)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<ADefenceEnemy> CurrentTarget;

	// 공격 스탯
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 700.0f;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackSpeed = 1.0f; // 1초에 한 번 공격s

	// 내부 타이머
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackTimer = 0.0f;

	// 실제 공격함수
	void FindTarget();
	void Attack();

protected:
	// 발 밑에 표시될 원
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	TObjectPtr<UDecalComponent> SelectionDecal;
};
