// Copyright Chukwuyenum Opone All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DD_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRONEDEFIANCE_API UDD_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category="Animation|Properties")
	void UpdateAnimationProperties(float DeltaTime);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	bool bIsAiming;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	bool bIsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	float LastMovementOffsetYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	float MovementOffsetYaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	FRotator RotationLastFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|Properties", meta=(AllowPrivateAccess = "true"))
	class ADD_CharacterBase* Character;
};
