// Copyright Chukwuyenum Opone All Rights Reserved


#include "Animation/DD_AnimInstance.h"

#include "Character/DD_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UDD_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ADD_CharacterBase>(TryGetPawnOwner());
}

void UDD_AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Character == nullptr)
	{
		Character = Cast<ADD_CharacterBase>(TryGetPawnOwner());
	}
	if (Character)
	{
		FVector Velocity{ Character->GetVelocity() };
		Velocity.Z =  0.f;
		Speed = Velocity.Size();
		bIsInAir = Character->GetCharacterMovement()->IsFalling();
		bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
		bIsAiming = Character->GetAiming();
		FRotator AimRotation = Character->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		if (Velocity.Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}
	}
}
