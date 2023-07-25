// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/MovementComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APotionBase::APotionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle Mesh"));
	BottleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->AttachToComponent(BottleMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
	matInst = UMaterialInstanceDynamic::Create(LiquidMesh->GetMaterial(0), this);
	LiquidMesh->SetMaterial(0, matInst);

	lastPos = GetActorLocation();
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

