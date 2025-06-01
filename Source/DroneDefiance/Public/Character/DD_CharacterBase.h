// Copyright Chukwuyenum Opone All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DD_CharacterBase.generated.h"

UCLASS()
class DRONEDEFIANCE_API ADD_CharacterBase : public ACharacter
{
	GENERATED_BODY()

	
public:
	// Sets default values for this character's properties
	ADD_CharacterBase();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	/** For Mouse */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	/** For GamePad */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookRateAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShootAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float BaseLookUpRate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void LookRate(const struct FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
