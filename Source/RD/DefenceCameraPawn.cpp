

#include "DefenceCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ADefenceCameraPawn::ADefenceCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = SpringArmComp;
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->TargetArmLength = 800.0f;
	SpringArmComp->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void ADefenceCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenceCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefenceCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

