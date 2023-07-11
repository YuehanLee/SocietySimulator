// Fill out your copyright notice in the Description page of Project Settings.


#include "SocietySimulatorCharacter.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"


// Sets default values
ASocietySimulatorCharacter::ASocietySimulatorCharacter()
{

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecal->SetupAttachment(RootComponent);
	SelectionDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	SelectionDecal->SetVisibility(false);
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASocietySimulatorCharacter::SetSelected() 
{
	SelectionDecal->SetVisibility(true);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Selected"));
}

void ASocietySimulatorCharacter::SetDeselected() 
{
	SelectionDecal->SetVisibility(false);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("Deselcted"));
}

// Called when the game starts or when spawned
void ASocietySimulatorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASocietySimulatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASocietySimulatorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

