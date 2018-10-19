// copyright Nikolaos Papadakis 2018

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/ActorComponent.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}



// Called when the gameUE_LOG(LogTemp, Warning, TEXT("Grapper Reporting for duty!!")); starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//look for attached physics handle
	FindPhysicsComponent();

	//look for attached input controller
	SetupInputComponent();

}

void  UGrabber::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle Component Found for %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	inComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found "));
		///Bind the input axis
		inComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No input Component Found for %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed "));
	GetFIrstPhysicsBodyInReach();
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released "));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Spooky Scary lines
//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 50, 25), true, 100.f, 0.f, 10.f);
//DrawDebugSphere(GetWorld(), PlayerViewPointLocation - 30, 20.f, 32, FColor(58, 32, 32), true, 100.f, SDPG_MAX, 10.f);

}

const FHitResult UGrabber::GetFIrstPhysicsBodyInReach()
{

	//Get Player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;

	///Setup query Parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()));
	}
	return FHitResult();
}

