
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefenceHUD.generated.h"

UCLASS()
class RD_API ADefenceHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// 매 프레임마다 화면을 그리는 함수
	virtual void DrawHUD() override;

	// 드래그 상태 관리 변수
	bool bIsDragging = false;	// 지금 드래그 중인가?
	bool bSelectPending = false; // 컨트롤러가 계산 신호 보낼 변수
	FVector2D InitialPoint;		// 마우스를 처음 누른 위치
	FVector2D CurrentPoint;		// 현재 마우스 위치
};
