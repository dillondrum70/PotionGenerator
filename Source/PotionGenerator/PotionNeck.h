// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "PotionNeck.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct POTIONGENERATOR_API FPotionNeck
{
	GENERATED_BODY()

public:
	FPotionNeck();
	~FPotionNeck();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> GlassMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> LiquidMesh;
};
