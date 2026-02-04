

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "DefencePath.generated.h"

UCLASS()
class RD_API ADefencePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefencePath();

	// 적들이 따라갈 곡선 경로
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Path")
	TObjectPtr<USplineComponent> SplineComponet;
};
