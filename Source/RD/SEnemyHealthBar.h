

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"	// 필수 헤더
#include "Widgets/DeclarativeSyntaxSupport.h"	// Slate 매크로 사용 지원
#include "Misc/Optional.h" // TOptional을 사용하기 위한 헤더

// 적 클래스 전방 선언
class ADefenceEnemy;

class RD_API SEnemyHealthBar : public SCompoundWidget
{
public:
	// Slate 매크로 시작 - 이 위젯을 생성할 때 받을 인자 (Argument)들을 정의
	SLATE_BEGIN_ARGS(SEnemyHealthBar) {}
		// 인자 1 : 이 체력바의 주인 (적 유닛)
		SLATE_ARGUMENT(TWeakObjectPtr<ADefenceEnemy>, OwnerEnemy)
	SLATE_END_ARGS()

	// 위젯을 조립하는 함수 (생성자 역할)
	void Construct(const FArguments& InArgs);

private:
	// 체력바의 주인을 기억할 변수 (WeakPtr는 주인이 죽으면 자동으로 null)(
	TWeakObjectPtr<ADefenceEnemy> EnemyOwner;

	// 매 프레임 체력 퍼센트를 계산해서 변환할 함수
	TOptional<float> GetHealthPercent() const;
};
