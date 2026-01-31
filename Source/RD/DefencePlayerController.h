
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefencePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABaseUnit;

UCLASS()
class RD_API ADefencePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADefencePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void HandleSelect();	// 좌 클릭
	void HandleMove();		// 우 클릭

	// 현재 선택된 유닛 저장
	UPROPERTY()
	TObjectPtr<ABaseUnit> SelectedUnit;

public:
	// 에디터 설정할 입력 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;	
};
