


#include "SEnemyHealthBar.h"
#include "DefenceEnemy.h" // 적 헤더 포함, 변수 접근용
#include "Widgets/Notifications/SProgressBar.h" // 프로그레스 바 헤더
#include "Widgets/Layout/SBox.h" // 박스 헤더
#include "Styling/CoreStyle.h" // 기본 스타일 사용을 위해 추가

void SEnemyHealthBar::Construct(const FArguments& InArgs)
{
	// 인자로 넘어온 주인 (Enemy)을 내 변수에 저장
	EnemyOwner = InArgs._OwnerEnemy;

	// UI 조립 (ChildSlot은 이 위젯의 몸통)
	ChildSlot
		[
			// 크기 고정을 위해 박스(SBox)로 감싸기
			SNew(SBox)
				.WidthOverride(100.0f) // 가로 길이
				.HeightOverride(15.0f)	// 세로 길이
				[
					// 그 안에 프로그레스 바(SProgressBar) 넣기
					SNew(SProgressBar)
						// 엔진 기본 스타일 적용
						.Style(FCoreStyle::Get(), "ProgressBar")
						// 왼쪽에서 오른쪽으로 차오르게 설정
						.BarFillType(EProgressBarFillType::LeftToRight)
						.Percent(this, &SEnemyHealthBar::GetHealthPercent)
						.FillColorAndOpacity(FSlateColor(FLinearColor::Green))
				]
		];
}

TOptional<float> SEnemyHealthBar::GetHealthPercent() const
{
	// 주인이 유효하다면
	if (EnemyOwner.IsValid())
	{
		// 0.0 ~ 1.0 사이의 비율 변환
		return EnemyOwner->CurrentHP / EnemyOwner->MaxHP;
	}

	return 0.0f; // 주인이 없으면 0%
}