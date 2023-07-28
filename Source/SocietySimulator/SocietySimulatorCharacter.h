// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SocietySimulatorResource.h"
#include "SocietySimulatorBuilding.h"
#include "SelectedUnitWidget.h"
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

	UFUNCTION()
	void SetSelected() ;
	UFUNCTION()
	void SetDeselected() ;
	void IsWorking(ASocietySimulatorResource* input);
	void ContinueWorking();
	void IsNotWorking() { isWorking = false; };
	void HaveResource() { haveResource = true; };
	void StoreResource() { haveResource = false; };
	USelectedUnitWidget* SelectedUnitWidget;
	float ProductionTime = 1;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* SelectionDecal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* UnitIcon;
	bool isWorking = false;
	ASocietySimulatorResource* SelectedResource;
	ASocietySimulatorBuilding* CollectResourceBuilding;
	float ShortestDistance = 50000;
	bool haveResource = false;
	//TSubclassOf<UUserWidget> SelectedUnitWidget;
	TSubclassOf<UUserWidget> SelectedUnitWidgetC;
	
	

};
