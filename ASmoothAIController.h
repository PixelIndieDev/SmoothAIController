#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ASmoothAIController.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API AASmoothAIController : public AAIController
{
	GENERATED_BODY()

protected:
	FRotator SmoothTargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SmoothFocusInterpSpeed = 2.0f;

public:
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;
};
