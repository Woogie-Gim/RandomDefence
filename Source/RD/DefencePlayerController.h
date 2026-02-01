
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
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

	// 에디터에서 WBP_MainHUD를 지정할 변수
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainHUDClass;

	// 생성된 위젯을 담아둘 변수
	UPROPERTY()
	TObjectPtr<UUserWidget> MainHUDInstance;
};
