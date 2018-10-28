// copyright Nikolaos Papadakis 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HHH_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Reach of the player
	float Reach = 130.f;

	UPhysicsHandleComponent * PhysicsHandle = nullptr;
		
	UInputComponent * inComponent = nullptr;
	
	//Ray-cast and grab in reach
	void Grab();
	
	void Release();

	///look for attached physics handle
	void FindPhysicsComponent();

	//setup input component
	void SetupInputComponent();

	//return hit for first physics body in reach
	const FHitResult GetFIrstPhysicsBodyInReach();

	//return current start of reach line
	FVector GetReachLineStart();

	//return current end of reach line
	FVector GetReachLineEnd();
};
