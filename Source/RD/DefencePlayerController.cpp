

#include "DefencePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h" // 이동 명령용

ADefencePlayerController::ADefencePlayerController()
{
	bShowMouseCursor = true; // 커서 보이기
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ADefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 입력 시스템 활성화
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADefencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 좌클릭 -> 선택, 우클릭 -> 이동
		if (SelectAction) EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ADefencePlayerController::HandleSelect);
		if (MoveAction) EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ADefencePlayerController::HandleMove);
	}
}

void ADefencePlayerController::HandleSelect()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ABaseUnit* NewUnit = Cast<ABaseUnit>(Hit.GetActor());

		if (SelectedUnit) SelectedUnit->SetSelectionState(false); // 기존 선택 해제

		if (NewUnit) // 유닛 클릭 시
		{
			SelectedUnit = NewUnit;
			SelectedUnit->SetSelectionState(true);
		}
		else // 빈 땅 클릭 시
		{
			SelectedUnit = nullptr;
		}
	}
}

void ADefencePlayerController::HandleMove()
{
	if (!SelectedUnit) return;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// AI 네비게이션을 이용해 이동
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedUnit->GetController(), Hit.Location);
	}
}