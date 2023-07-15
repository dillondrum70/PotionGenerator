// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APotionBase::APotionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle Mesh"));
	bottleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	liquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	liquidMesh->AttachToComponent(bottleMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

