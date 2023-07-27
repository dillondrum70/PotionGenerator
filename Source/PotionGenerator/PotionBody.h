// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "PotionBody.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct POTIONGENERATOR_API FPotionBody
{
	GENERATED_BODY()

public:
	FPotionBody();
	~FPotionBody();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> GlassMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> LiquidMesh;
};
