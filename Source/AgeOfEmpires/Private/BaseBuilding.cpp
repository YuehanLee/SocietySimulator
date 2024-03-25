#include "BaseBuilding.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize production rates (in seconds)
    TimeBetweenUnitProduction = 10.0f; // Every 10 seconds
    TimeBetweenBuildingProduction = 30.0f; // Every 30 seconds
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
    Super::BeginPlay();

    // Start timers for unit and building production
    GetWorld()->GetTimerManager().SetTimer(UnitProductionTimerHandle, this, &ABaseBuilding::ProduceUnit, TimeBetweenUnitProduction, true);
    GetWorld()->GetTimerManager().SetTimer(BuildingProductionTimerHandle, this, &ABaseBuilding::BuildStructure, TimeBetweenBuildingProduction, true);
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Implement unit production logic
void ABaseBuilding::ProduceUnit()
{
    UE_LOG(LogTemp, Warning, TEXT("Producing unit..."));
    // Here you would spawn a unit actor
}

// Implement building production logic
void ABaseBuilding::BuildStructure()
{
    UE_LOG(LogTemp, Warning, TEXT("Building structure..."));
    // Here you would spawn a building actor
}
