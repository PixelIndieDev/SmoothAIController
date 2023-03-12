#include "ASmoothAIController.h"
#include "Kismet/KismetMathLibrary.h"

void AASmoothAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn) {
		FRotator NewControlRotation = GetControlRotation();

		// Look toward focus
		const FVector FocalPoint = GetFocalPoint();
		if (FAISystem::IsValidLocation(FocalPoint)) {
			NewControlRotation = (FocalPoint - MyPawn->GetPawnViewLocation()).Rotation();
		}
		else if (bSetControlRotationFromPawnOrientation) {
			NewControlRotation = MyPawn->GetActorRotation();
		}

		SetControlRotation(NewControlRotation);

		//Smooth and change the pawn rotation
		if (bUpdatePawn)
		{
			//Get Pawn current rotation
			const FRotator CurrentPawnRotation = MyPawn->GetActorRotation();

			//Calculate smoothed rotation
			SmoothTargetRotation = UKismetMathLibrary::RInterpTo(MyPawn->GetActorRotation(), ControlRotation, DeltaTime, SmoothFocusInterpSpeed);
			//Check if we need to change
			if (CurrentPawnRotation.Equals(SmoothTargetRotation, 1e-3f) == false)
			{
				//Change rotation using the Smooth Target Rotation
				MyPawn->FaceRotation(SmoothTargetRotation, DeltaTime);
			}
		}
	}
}