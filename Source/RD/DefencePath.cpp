


#include "DefencePath.h"

// Sets default values
ADefencePath::ADefencePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// 길은 움직이지 않으니 Tick 꺼둠 (최적화)

	// 스플라인 컴포넌트 생성
	SplineComponet = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponet;
}

