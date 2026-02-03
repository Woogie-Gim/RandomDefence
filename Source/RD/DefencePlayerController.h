
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DefenceHUD.h"
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
	// HUD를 제어하기 위한 포인터
	UPROPERTY()
	TObjectPtr<ADefenceHUD> DefenceHUD;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void HandleSelectStart();		// 눌렀을 때
	void HandleSelectTriggered();	// 드래그 중일 때
	void HandleSelectComplete();	// 손 뗐을 때 (최종 선택)
	void HandleMove();				// 우 클릭

public:
	// 에디터 설정할 입력 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;	

	// 에디터에서 WBP_MainHUD를 지정할 변수
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainHUDClass;

	// 생성된 위젯을 담아둘 변수
	UPROPERTY()
	TObjectPtr<UUserWidget> MainHUDInstance;

	// 현재 선택된 유닛 저장
	// [변경] 단일 포인터 -> 배열 (여러 유닛 선택)
	// UPROPERTY()
	// TObjectPtr<ABaseUnit> SelectedUnit;
	UPROPERTY()
	TArray<TObjectPtr<ABaseUnit>> SelectedUnits;
};
