

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// 전방 선언
class USphereComponent;
class UProjectileMovementComponent;
class ADefenceEnemy;

UCLASS()
class RD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> CollisionComponent; // 충돌 감지용

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<UStaticMeshComponent> MeshComponent; // 눈에 보이는 화살 / 마법

	UPROPERTY(VisibleDefaultsOnly, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement; // 날아 가게 하는 엔진

	// 데이터
	TObjectPtr<ADefenceEnemy> TargetEnemy; // 누구를 따라갈지
	float DamageValue = 0.0f;	// 데미지

	// 함수
	// 유닛이 투사체를 소환한 직후에 호출해서 정보를 넘겨주는 함수
	void Initialize(ADefenceEnemy* Target, float Damage);

	// 충돌 시 호출될 함수
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
