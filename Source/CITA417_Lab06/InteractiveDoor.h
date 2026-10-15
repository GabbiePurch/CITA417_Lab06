
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableTarget.h"
#include "InteractiveDoor.generated.h"

UCLASS()
class CITA417_LAB06_API AInteractiveDoor
    : public AActor, public IInteractableTarget
{
    GENERATED_BODY()

public:

    virtual void ActivateTarget_Implementation() override;

    AInteractiveDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    void OpenDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    void CloseDoor();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    FVector OpenOffset = FVector(0.0f, 0.0f, 250.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float MoveSpeed = 150.0f;

private:
    FVector ClosedLocation;
    FVector OpenLocation;

    bool bShouldOpen = false;

public:
    virtual void Tick(float DeltaTime) override;
};
