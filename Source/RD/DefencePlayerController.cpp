

#include "DefencePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h" // 이동 명령용
#include "DefenceHUD.h"
#include "Framework/Application/SlateApplication.h" // 마우스 좌표 가져오기용

ADefencePlayerController::ADefencePlayerController()
{
	bShowMouseCursor = true; // 커서 보이기
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ADefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 내 HUD
	DefenceHUD = Cast<ADefenceHUD>(GetHUD());

	// 입력 시스템 활성화
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// UI 생성 및 화면 부착
	if (MainHUDClass)
	{
		MainHUDInstance = CreateWidget<UUserWidget>(this, MainHUDClass);
		if (MainHUDInstance)
		{
			MainHUDInstance->AddToViewport();
		}
	}
}

void ADefencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// SelectAction(좌클릭)에 3r가지 타이밍 연결
		// 1. Started : 누르자마자 (초기화)
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ADefencePlayerController::HandleSelectStart);
		// 2. Triggered : 누르고 있는 동안(사각형 그리기)
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ADefencePlayerController::HandleSelectTriggered);
		// 3. Completed : 손을 뗐을 때 (유닛 찾기)
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ADefencePlayerController::HandleSelectComplete);
		
		// 유닛 무빙
		if (MoveAction) EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ADefencePlayerController::HandleMove);
	}
}

// 1. 마우스 클릭 (초기화 단계)
void ADefencePlayerController::HandleSelectStart()
{
	// 기존에 선택된 유닛들 모두 해제 (원형 끄기)
	for (ABaseUnit* Unit : SelectedUnits)
	{
		if (Unit) Unit->SetSelectionState(false);
	}
	SelectedUnits.Empty(); // 배열 비우기

	// HUD에게 그림 그릴 준비 명령
	if (DefenceHUD)
	{
		DefenceHUD->bIsDragging = true;
		float MouseX, MouseY;
		GetMousePosition(MouseX, MouseY); // 현재 마우스 좌표
		DefenceHUD->InitialPoint = FVector2D(MouseX, MouseY); // 시작점 저장
	}
}

// 2. 드래그 중 (시각적 업데이트)
void ADefencePlayerController::HandleSelectTriggered()
{
	if (DefenceHUD)
	{
		float MouseX, MouseY;
		GetMousePosition(MouseX, MouseY);
		DefenceHUD->CurrentPoint = FVector2D(MouseX, MouseY); // 끝점 계속 갱신
	}
}

// 3. 마우스 뗌 (최종 선택)
void ADefencePlayerController::HandleSelectComplete()
{
	if (DefenceHUD)
	{
		DefenceHUD->bIsDragging = false; // 드래그 시각 효과 끄기
		DefenceHUD->bSelectPending = true; // 다음 프레임에 계산 명령
	}
}

// 4. 이동 명령
void ADefencePlayerController::HandleMove()
{
	if (SelectedUnits.Num() == 0) return;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// 선택된 모든 유닛에게 움직임 명령
		for (ABaseUnit* Unit : SelectedUnits)
		{
			if (Unit && Unit->GetController())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(Unit->GetController(), Hit.Location);
			}
		}
	}
}