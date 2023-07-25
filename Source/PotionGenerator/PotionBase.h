// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionBase.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UMaterialInstanceDynamic;
class UMovementComponent;

UCLASS()
class POTIONGENERATOR_API APotionBase : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Model, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BottleMesh;
	UPROPERTY(EditAnywhere, Category = Model, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> LiquidMesh;

	UPROPERTY(EditAnywhere, Category = Material, meta = (AllowPrivateAccess = "true"))
	FName WobbleXName = TEXT("WobbleX");
	UPROPERTY(EditAnywhere, Category = Material, meta = (AllowPrivateAccess = "true"))
	FName WobbleYName = TEXT("WobbleY");

	TObjectPtr<UMaterialInstanceDynamic> matInst;

	float WobbleX = 0;	//Wobble amount coefficient based on velocity
	float TargetWobbleX = 0;	//Coefficient combined with Sin to achieve wobbling effect

	float WobbleY = 0;
	float TargetWobbleY = 0;

	FVector lastPos;

	UPROPERTY(EditAnywhere, Category = Potion, meta = (AllowPrivateAccess = "true"))
	float WobbleSpeed = 3;	//Lower value = higher viscocity
	UPROPERTY(EditAnywhere, Category = Potion, meta = (AllowPrivateAccess = "true"))
	float WobbleLimit = .75f;	//Maximum angle of liquid as it oscillates, 1 is completely horizontal (so the surface points sideways)
	UPROPERTY(EditAnywhere, Category = Potion, meta = (AllowPrivateAccess = "true"))
	float VelocitySmoothing = 10.0f;	//Amount by which velocity is divided to remove jittery, sudden changes in velocity
	
public:	
	// Sets default values for this actor's properties
	APotionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
