

#include "DefenceHUD.h"
#include "DefencePlayerController.h"
#include "BaseUnit.h"

void ADefenceHUD::DrawHUD()
{
	Super::DrawHUD();

	// 드래그 중일 때만 사각형을 그림
	if (bIsDragging)
	{
		// 사각형 색상 (초록색, 반투명)
		FLinearColor RectColor = FLinearColor(0.2f, 0.8f, 0.2f, 0.2f);

		// 사각형 그리기 (StartX, StartY, Width, Height, Color)
		DrawRect(RectColor, InitialPoint.X, InitialPoint.Y,
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
	}

	// 드래그 끝날 때 유닛 찾기
	if (bSelectPending)
	{
		// 유닛 찾기
		TArray<ABaseUnit*> OutActors;
		GetActorsInSelectionRectangle<ABaseUnit>(InitialPoint, CurrentPoint, OutActors, false, false);

		// 찾은 결과를 컨트롤러에게 전달
		// GetOwningPlayerController()는 HUD의 주인 컨트롤러를 가져온다
		if (ADefencePlayerController* PC = Cast<ADefencePlayerController>(GetOwningPlayerController()))
		{
			// 기존 선택 해제 (원 끄기)
			for (ABaseUnit* Unit : PC->SelectedUnits)
			{
				if (Unit) Unit->SetSelectionState(false);
			}
			PC->SelectedUnits.Empty();

			// 새로 찾은 유닛 넣기
			for (ABaseUnit* Unit : OutActors)
			{
				if (Unit)
				{
					PC->SelectedUnits.Add(Unit);
					Unit->SetSelectionState(true); // 선택 효과 켜기
				}
			}
		}

		// 계산 끝났으니
		bSelectPending = false;
	}
}
