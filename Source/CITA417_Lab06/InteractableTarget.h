// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableTarget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class CITA417_LAB06_API IInteractableTarget
{
    GENERATED_BODY()

public:

    // Common function for any interactive target
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable,
        Category = "Interaction")
    void ActivateTarget();
};

