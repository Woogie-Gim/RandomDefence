
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "DefenceEnemy.h"
#include "BaseUnit.generated.h"

// 전방 선언
class UDecalComponent; 
class AProjectile;

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

	// 블루프린트에서 설정할 투사체 클라스
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	// 공격 애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	// 실제 공격함수
	void FindTarget();
	virtual void Attack();

	// 실제로 판매를 실행하는 함수 (UI의 판매 버튼을 누르면 호출될 예정)
	UFUNCTION(BlueprintCallable, Category = "Economy")
	void ExecuteSell();

protected:
	// 발 밑에 표시될 원
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	TObjectPtr<UDecalComponent> SelectionDecal;

	// 블루프린트에게 UI 띄우라고 명렴안 내릴 이벤트 (C++ 에선 구현 안함)
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowSellUI();

	// 블루프린트에게 UI 지우라고 명령하는 이벤트
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void HideSellUI();
};
