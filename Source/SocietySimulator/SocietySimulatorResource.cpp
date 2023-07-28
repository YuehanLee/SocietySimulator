// Fill out your copyright notice in the Description page of Project Settings.


#include "SocietySimulatorResource.h"
#include "SocietySimulatorCharacter.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"

// Sets default values
ASocietySimulatorResource::ASocietySimulatorResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	//SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	//SelectionDecal->SetupAttachment(RootComponent);
	//SelectionDecal->SetVisibility(false);
	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	ResourceMesh->SetupAttachment(RootComponent);
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASocietySimulatorResource::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASocietySimulatorResource::BeginOverlap);
	
}

void ASocietySimulatorResource::BeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("resourceoverlapped"));
	ASocietySimulatorCharacter* CollideCharacter = Cast<ASocietySimulatorCharacter>(OtherActor);
	if (CollideCharacter) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("resourceoverlapped2"));
		CollideCharacter->HaveResource();
		CollideCharacter->IsWorking(this);
	}
}

// Called every frame
void ASocietySimulatorResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

