

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "DefenceEnemy.generated.h"

class USplineComponent;

UCLASS()
class RD_API ADefenceEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefenceEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 스포너가 적을 소환할 때 길을 안내 하는 함수
	void SetPath(USplineComponent* NewSpline);

	// 체력 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float CurrentHP;

	// 죽었는지 확인하는 변수
	bool bIsDead = false;

	// 데미지 받는 함수 (외부에서 호출)
	UFUNCTION(BlueprintCallable)
	void OnTakeDamage(float DamageAmount);

	// 사망 애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	// 투명도 조절 동적 머터리얼 인스턴스
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	// 현재 투명도 값 (1.0 = 불투명, 0.0 = 투명)
	float CurrentOpacity = 1.0f;

	// 투명해지는 속도 (값이 클수록 빨리 사라짐)
	UPROPERTY(EditAnywhere, Category = "Visuals")
	float FadeOutSpeed = 0.5f;

protected:
	// 이동 관련 변수
	UPROPERTY()
	TObjectPtr<USplineComponent> PathSpline;

	// 내가 길의 몇 미터 지점에 있는지
	float CurrentDistance = 0.0f;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float MoveSpeed = 300.0f;
};
