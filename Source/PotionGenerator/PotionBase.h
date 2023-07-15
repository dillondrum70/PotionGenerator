// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class POTIONGENERATOR_API APotionBase : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Model, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> bottleMesh;
	
	UPROPERTY(EditAnywhere, Category = Model, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> liquidMesh;
	
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
