
#include "InteractiveDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractiveDoor::AInteractiveDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the door mesh
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));

    RootComponent = DoorMesh;
}

// Called when the game starts
void AInteractiveDoor::BeginPlay()
{
    Super::BeginPlay();

    // Remember where the door starts
    ClosedLocation = GetActorLocation();

    // Calculate where the door should open
    OpenLocation = ClosedLocation + OpenOffset;

    UE_LOG(LogTemp, Warning, TEXT("Interactive Door Initialized!"));
}

// Called every frame
void AInteractiveDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector TargetLocation;

    if (bShouldOpen)
    {
        TargetLocation = OpenLocation;
    }
    else
    {
        TargetLocation = ClosedLocation;
    }

    // Move smoothly toward the target
    FVector NewLocation = FMath::VInterpConstantTo(
        GetActorLocation(),
        TargetLocation,
        DeltaTime,
        FMath::Max(0.0f, MoveSpeed)
    );

    SetActorLocation(NewLocation);
}

// Called when the pressure plate activates
void AInteractiveDoor::OpenDoor()
{
    if (!bShouldOpen)
    {
        bShouldOpen = true;

        UE_LOG(LogTemp, Warning, TEXT("Door Opening!"));
    }
}

// Called when the pressure plate deactivates
void AInteractiveDoor::CloseDoor()
{
    if (bShouldOpen)
    {
        bShouldOpen = false;

        UE_LOG(LogTemp, Warning, TEXT("Door Closing!"));
    }
}

