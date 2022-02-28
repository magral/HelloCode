// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HelloSphere.generated.h"

UCLASS()
class HELLOCODE_API AHelloSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelloSphere();

protected:
	class UTextRenderComponent* TextRenderComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MakeParticleSystem(UStaticMeshComponent* sphereVisual);
	void MakeTextComponent(UStaticMeshComponent* sphereVisual);
	void AssignMaterial(UStaticMeshComponent* sphereVisual);
	void AssignMeshVisuals(UStaticMeshComponent* sphereVisual);
	UFUNCTION()	
	void MyOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	void MyOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
