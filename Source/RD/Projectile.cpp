


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DefenceEnemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 유도 기능을 위해 틱 켜기
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체(구체) 설정
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));	// 적과 겹침 감지
	RootComponent = CollisionComponent;

	// 충돌 이벤트 연결 (부딪히면 OnOverlapBegin 실행)
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

	// 메쉬 설정
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메쉬는 충돌 판정 x (구체가 대신함)

	// 무브먼테 (엔진) 설정
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true; // 날아가는 방향으로 회전
	ProjectileMovement->ProjectileGravityScale = 0.0f; // 중력 0 (직사)

	InitialLifeSpan = 5.0f; // 5초 뒤에 자동으로 사라짐 (메모리 관리)
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 유도 기능 : 타겟이 살아있다면 그 쪽으로 방향을 전환
	if (TargetEnemy && !TargetEnemy->bIsDead && ProjectileMovement)
	{
		FVector TargetLocation = TargetEnemy->GetActorLocation();
		TargetLocation.Z += 50.0f; // 적의 발 밑 말고 가슴 쪽을 노리게 높이 조절

		// 방향 계산 : (목표점 - 내 위치)
		FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();

		// 속도 갱신
		ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
	}
}

void AProjectile::Initialize(ADefenceEnemy* Target, float Damage)
{
	TargetEnemy = Target;
	DamageValue = Damage;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 게 내가 노리던 적 유닛인지 확인
	if (OtherActor && (OtherActor != this) && OtherActor == TargetEnemy)
	{
		ADefenceEnemy* Enemy = Cast<ADefenceEnemy>(OtherActor);

		if (Enemy)
		{
			// 데미지 전달
			Enemy->OnTakeDamage(DamageValue);

			// 할 일 다 했으니 삭제
			Destroy();
		}
	}
}

