// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/MovementComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/StaticMesh.h"

// Sets default values
APotionBase::APotionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle Mesh"));
	BottleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	NeckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Neck Mesh"));
	NeckMesh->AttachToComponent(BottleMesh, FAttachmentTransformRules::KeepRelativeTransform);

	CorkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cork Mesh"));
	CorkMesh->AttachToComponent(BottleMesh, FAttachmentTransformRules::KeepRelativeTransform);

	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->AttachToComponent(BottleMesh, FAttachmentTransformRules::KeepRelativeTransform);

	LiquidNeckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Neck Mesh"));
	LiquidNeckMesh->AttachToComponent(BottleMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
	matInst = UMaterialInstanceDynamic::Create(LiquidMesh->GetMaterial(0), this);
	LiquidMesh->SetMaterial(0, matInst);

	lastPos = GetActorLocation();

	int bodyIndex = FMath::RandRange(0, PotionBodies.Num() - 1);
	BottleMesh->SetStaticMesh(PotionBodies[bodyIndex].GlassMesh);
	LiquidMesh->SetStaticMesh(PotionBodies[bodyIndex].LiquidMesh);

	int neckIndex = FMath::RandRange(0, PotionNecks.Num() - 1);
	NeckMesh->SetStaticMesh(PotionNecks[neckIndex].GlassMesh);
	LiquidNeckMesh->SetStaticMesh(PotionNecks[neckIndex].LiquidMesh);

	int corkIndex = FMath::RandRange(0, PotionCorks.Num() - 1);
	CorkMesh->SetStaticMesh(PotionCorks[neckIndex]);
}

// Called every frame
void APotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WobbleX = FMath::Lerp(WobbleX, 0, DeltaTime * WobbleSpeed);
	WobbleY = FMath::Lerp(WobbleY, 0, DeltaTime * WobbleSpeed);

	float pulse = 2 * PI * WobbleSpeed;
	TargetWobbleX = WobbleX * FMath::Sin(pulse * GetWorld()->GetTime().GetRealTimeSeconds());
	TargetWobbleY = WobbleY * FMath::Sin(pulse * GetWorld()->GetTime().GetRealTimeSeconds());

	FVector vel = (lastPos - GetActorLocation()) / VelocitySmoothing;
	WobbleX = FMath::Clamp(WobbleX + (-vel.Y * WobbleLimit), -WobbleLimit, WobbleLimit);
	WobbleY = FMath::Clamp(WobbleY + (vel.X * WobbleLimit), -WobbleLimit, WobbleLimit);

	matInst->SetScalarParameterValue(WobbleXName, TargetWobbleX);
	matInst->SetScalarParameterValue(WobbleYName, TargetWobbleY);


	/*FVector vel = lastPos - GetActorLocation();
	TargetWobbleX = -vel.Y;
	TargetWobbleY = vel.X;

	WobbleX = FMath::Clamp(FMath::Lerp(WobbleX, TargetWobbleX, WobbleSpeed * DeltaTime), -WobbleLimit, WobbleLimit);
	WobbleY = FMath::Clamp(FMath::Lerp(WobbleY, TargetWobbleY, WobbleSpeed * DeltaTime), -WobbleLimit, WobbleLimit);
		
	*/

	lastPos = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("%f  %f"), WobbleX, WobbleY);
}

