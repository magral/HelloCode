// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
#include <Runtime/Engine/Classes/Components/SphereComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
	// Our root component will be a sphere component that will inform us of overlaps and collisions
	USphereComponent* sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = sphereComponent;

	// Asign Properties to SphereComponent
	sphereComponent->InitSphereRadius(220.f);
	sphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// Create and Attach a sphere mesh 
	UStaticMeshComponent* sphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	sphereVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AssignMeshVisuals(sphereVisual);
	MakeParticleSystem(sphereVisual);
	MakeTextComponent(sphereVisual);

	// Bind Delegates
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBeginOverlap);
	sphereComponent->OnComponentEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);

	// Assign Material
	AssignMaterial(sphereVisual);
}

void AHelloSphere::MakeParticleSystem(UStaticMeshComponent* sphereVisual) {
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));

	FireParticles->AttachToComponent(sphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	FireParticles->bAutoActivate = true;

	// Assign fire particle system to component
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));

	if (FireVisual.Succeeded()) {
		FireParticles->SetTemplate(FireVisual.Object);
	}
}

void AHelloSphere::MakeTextComponent(UStaticMeshComponent* sphereVisual) {
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	TextRenderComponent->AttachToComponent(sphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));

	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}

void AHelloSphere::AssignMaterial(UStaticMeshComponent* sphereVisual) {
	ConstructorHelpers::FObjectFinder<UMaterial>SphereMatieral(TEXT("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel"));

	if (SphereMatieral.Succeeded()) {
		sphereVisual->SetMaterial(0, SphereMatieral.Object);
		sphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	}
}

void AHelloSphere::AssignMeshVisuals(UStaticMeshComponent* sphereVisual) {
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	// Adjust Properties of the mesh if mesh asset was found
	if (SphereAsset.Succeeded()) {
		sphereVisual->SetStaticMesh(SphereAsset.Object);
		sphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
}

void AHelloSphere::MyOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) {
	FString outputString;
	outputString = "Hello" + OtherActor->GetName() + "!";
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex) {
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

