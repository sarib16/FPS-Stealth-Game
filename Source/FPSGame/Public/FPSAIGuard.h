// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alert
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Conponents")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* PawnSeen);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	UFUNCTION()
	void SetGuardState(EAIState  NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState  NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// AI Patrol Code

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	TArray<AActor*> PatrolPoints;

	int LastPatrolPointIndex;

	AActor* CurrentPatrolPoint;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	float DistanceToGoal;

	UFUNCTION()
	void MoveToNextPatrolPoint();


};
