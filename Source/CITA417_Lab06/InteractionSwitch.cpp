// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSwitch.h"
#include "InteractableTarget.h"
#include "GameFramework/Pawn.h"

// Sets default values
AInteractionSwitch::AInteractionSwitch()
{
    PrimaryActorTick.bCanEverTick = false;

    InteractionRange = CreateDefaultSubobject<UBoxComponent>(
        TEXT("InteractionRange")
    );

    RootComponent = InteractionRange;

    InteractionRange->SetBoxExtent(FVector(150.0f, 150.0f, 100.0f));
    InteractionRange->SetCollisionProfileName(TEXT("Trigger"));
    InteractionRange->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AInteractionSwitch::BeginPlay()
{
    Super::BeginPlay();

    InteractionRange->OnComponentBeginOverlap.AddDynamic(
        this, &AInteractionSwitch::OnRangeBeginOverlap
    );

    InteractionRange->OnComponentEndOverlap.AddDynamic(
        this, &AInteractionSwitch::OnRangeEndOverlap
    );

    UE_LOG(LogTemp, Warning, TEXT("Interaction Switch Initialized!"));
}

// Called every frame
void AInteractionSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AInteractionSwitch::OnRangeBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!IsValid(OtherActor) ||
        !OtherActor->ActorHasTag(FName(TEXT("Player"))))
    {
        return;
    }

    bPlayerInRange = true;

    UE_LOG(LogTemp, Warning,
        TEXT("Player entered interaction switch range!"));
}

void AInteractionSwitch::OnRangeEndOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (!IsValid(OtherActor) ||
        !OtherActor->ActorHasTag(FName(TEXT("Player"))))
    {
        return;
    }

    bPlayerInRange = false;

    UE_LOG(LogTemp, Warning,
        TEXT("Player left interaction switch range!"));
}




void AInteractionSwitch::Interact()
{
    // Make sure the player is in range
    if (!bPlayerInRange)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Interaction failed: Player is not in range!"));
        return;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("Interaction Switch Activated!"));

    // Notify anything listening to our event
    OnSwitchActivated.Broadcast();

    UE_LOG(LogTemp, Warning,
        TEXT("Interaction Switch broadcast its activation event!"));

    // Make sure targets have been assigned
    if (TargetActors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Interaction Switch has no target actors assigned!"));
        return;
    }

    // Activate every valid target through our interface
    for (AActor* Target : TargetActors)
    {
        if (!IsValid(Target))
        {
            UE_LOG(LogTemp, Warning,
                TEXT("Interaction Switch has an invalid target reference!"));
            continue;
        }

        // Check whether this Actor supports our interface
        if (!Target->GetClass()->ImplementsInterface(
            UInteractableTarget::StaticClass()))
        {
            UE_LOG(LogTemp, Warning,
                TEXT("Target %s does not implement InteractableTarget!"),
                *Target->GetName());
            continue;
        }

        // Call the interface function
        IInteractableTarget::Execute_ActivateTarget(Target);

        UE_LOG(LogTemp, Warning,
            TEXT("Interaction Switch activated target: %s"),
            *Target->GetName());
    }
}

