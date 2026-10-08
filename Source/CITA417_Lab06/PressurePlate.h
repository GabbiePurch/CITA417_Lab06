
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InteractiveDoor.h"
#include "PressurePlate.generated.h"

UCLASS()
class CITA417_LAB06_API APressurePlate : public AActor
{
    GENERATED_BODY()

public:
    APressurePlate();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    UBoxComponent* TriggerBox;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Interaction")
    AInteractiveDoor* TargetDoor = nullptr;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float ActivationDelay = 0.0f;

private:

    bool bPlayerOnPlate = false;

    bool bPlateActivated = false;

    float ActivationTimer = 0.0f;


    UFUNCTION()
    void OnTriggerBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UFUNCTION()
    void OnTriggerEndOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );

public:
    virtual void Tick(float DeltaTime) override;
};
