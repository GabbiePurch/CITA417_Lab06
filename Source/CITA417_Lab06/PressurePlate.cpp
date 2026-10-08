
#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

APressurePlate::APressurePlate()
{
    PrimaryActorTick.bCanEverTick = true;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);
}

void APressurePlate::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(
        this, &APressurePlate::OnTriggerBeginOverlap
    );

    TriggerBox->OnComponentEndOverlap.AddDynamic(
        this, &APressurePlate::OnTriggerEndOverlap
    );

    UE_LOG(LogTemp, Warning, TEXT("Pressure Plate initialized!"));
}


void APressurePlate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bPlayerOnPlate && !bPlateActivated)
    {
        ActivationTimer += DeltaTime;

        if (ActivationTimer >= ActivationDelay)
        {
            bPlateActivated = true;

            if (TargetDoor)
            {
                TargetDoor->OpenDoor();

                UE_LOG(LogTemp, Warning,
                    TEXT("Pressure Plate Activated after %.1f seconds!"),
                    ActivationTimer);
            }
            else
            {
                UE_LOG(LogTemp, Warning,
                    TEXT("Pressure Plate has no Target Door assigned!"));
            }
        }
    }
}


void APressurePlate::OnTriggerBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)

{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    // Only allow the player to activate the plate
    if (!OtherActor->IsA<APawn>())
    {
        return;
    }

    bPlayerOnPlate = true;
    ActivationTimer = 0.0f;

    UE_LOG(LogTemp, Warning,
        TEXT("Player stepped onto pressure plate!"));

    // Activate immediately if there is no delay
    if (ActivationDelay <= 0.0f && !bPlateActivated)
    {
        bPlateActivated = true;

        if (TargetDoor)
        {
            TargetDoor->OpenDoor();
        }
        else
        {
            UE_LOG(LogTemp, Warning,
                TEXT("Pressure Plate has no Target Door assigned!"));
        }
    }
}


void APressurePlate::OnTriggerEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex
)

{
    if (!OtherActor || !OtherActor->IsA<APawn>())
    {
        return;
    }

    bPlayerOnPlate = false;
    ActivationTimer = 0.0f;

    if (bPlateActivated)
    {
        bPlateActivated = false;

        if (TargetDoor)
        {
            TargetDoor->CloseDoor();
        }

        UE_LOG(LogTemp, Warning,
            TEXT("Pressure Plate Deactivated!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Player left before activation!"));
    }
}

