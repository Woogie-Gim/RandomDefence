

#include "BaseUnit.h"
#include "Components/DecalComponent.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 최적화 : 틱 끄기
	PrimaryActorTick.bCanEverTick = false;

	// 데칼 컴포넌트 생성 및 설정
	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	// 안보이는 기본 상태
	SelectionDecal->SetVisibility(false); 

	// 데칼 -90도 회전
	SelectionDecal->SetRelativeRotation(FRotator(- 90.0f, 0.0f, 0.0f));
	SelectionDecal->DecalSize = FVector(128.0f, 128.0f, 128.0f);

}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseUnit::SetSelectionState(bool bIsSelected)
{
	if (SelectionDecal)
	{
		SelectionDecal->SetVisibility(bIsSelected);
	}
}

