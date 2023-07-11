// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SocietySimulatorCharacter.generated.h"

UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASocietySimulatorCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FORCEINLINE class UDecalComponent* GetSelectionDecal() { return SelectionDecal; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSelected();
	void SetDeselected();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* SelectionDecal;

};
