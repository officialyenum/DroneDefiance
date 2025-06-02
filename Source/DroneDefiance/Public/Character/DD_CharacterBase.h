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

	/** Input Area */
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
	TObjectPtr<class UInputAction> FireWeaponAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AimWeaponAction;

	/** Camera Rotations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float HipTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float HipLookUpRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float AimingTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float AimingLookUpRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float MouseHipTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float MouseHipLookUpRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float MouseAimingTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float MouseAimingLookUpRate;

	
	float CameraDefaultFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float CameraZoomedFOV;
	float CameraCurrentFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Camera", meta=(AllowPrivateAccess = "true"))
	float ZoomedInterpSpeed;

	/** Weapons and Combat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	class USoundCue* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* SmokeTrailParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Combat|Weapon", meta=(AllowPrivateAccess = "true"))
	bool bAiming;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void LookRate(const struct FInputActionValue& Value);
	void FireWeapon();
	void AimButtonPressed();
	void AimButtonReleased();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);
	void InterpCameraZoom(float DeltaTime);
	void SetLookRates();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool GetAiming() const { return bAiming; }
};
