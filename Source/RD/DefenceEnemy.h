

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
