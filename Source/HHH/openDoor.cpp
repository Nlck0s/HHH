// copyright Nikolaos Papadakis 2018

#include "openDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UopenDoor::UopenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UopenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Something Missing Pressure plate"));
	}
}


// Called every frame
void UopenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("%f kg"),GetTotalMassOnPlate());
	if (GetTotalMassOnPlate() == TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}

}

float UopenDoor::GetTotalMassOnPlate() {

	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Temp : OverlappingActors)
	{
		TotalMass += Temp->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is inposition"), *Temp->GetName());
	}

	return TotalMass;
}