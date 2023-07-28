// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectedBuildingWidget.h"
//#include "ProduceUnitWidget.h"
//#include "SocietySimulatorCharacter.h"
#include "SocietySimulatorBuilding.generated.h"

UCLASS()
class SOCIETYSIMULATOR_API ASocietySimulatorBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocietySimulatorBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FORCEINLINE class UDecalComponent* GetSelectionDecal() { return SelectionDecal; }
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSelected();
	void SetDeselected();
	USelectedBuildingWidget* SelectedBuildingWidget;
	TArray<UUserWidget*> ActionBoxButton;
	//UProduceUnitWidget* ProduceUnitWidget;
	bool IsProducingUnit;
	void AddUnitToQueue(TSubclassOf<AActor> Unit);
	float ProductionTimeSpend;
	float CurrentProductionTime;
	float ProductionProgress;
	TSubclassOf<AActor> UnitBeingProduced;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* SelectionDecal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BuildingMesh;
	TSubclassOf<UUserWidget> SelectedBuildingWidgetC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* BuildingIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	FString BuildingName;
	TSubclassOf<UUserWidget> ActionBoxButton1C;
	TArray<TSubclassOf<AActor>> UnitProductionQueue;
};
