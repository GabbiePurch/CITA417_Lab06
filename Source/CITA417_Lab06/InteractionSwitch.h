// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/boxComponent.h"
#include "InteractableTarget.h"
#include "InteractionSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchActivated);

UCLASS()
class CITA417_LAB06_API AInteractionSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionSwitch();

	UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
	FOnSwitchActivated OnSwitchActivated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision box used to detect nearby players
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UBoxComponent* InteractionRange;

	// Tracks whether the player is close enough to interact
	bool bPlayerInRange = false;


	// Doors controlled by this interaction switch
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly,
		Category = "Interaction",
		meta = (MustImplement = "/Script/CITA417_Lab06.InteractableTarget"))
	TArray<TObjectPtr<AActor>> TargetActors;



	UFUNCTION()
	void OnRangeBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnRangeEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

};
