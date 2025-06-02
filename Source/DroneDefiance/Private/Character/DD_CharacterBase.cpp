// Copyright Chukwuyenum Opone All Rights Reserved


#include "Character/DD_CharacterBase.h"


#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


// Sets default values
ADD_CharacterBase::ADD_CharacterBase() :
// Base rates for look sensitivity scale factor
BaseTurnRate(45.f),
BaseLookUpRate(45.f),
// Game Pad Look Sensitivity Scale Factor
HipTurnRate(90.f),
HipLookUpRate(90.f),
AimingTurnRate(20.f),
AimingLookUpRate(20.f),
// Mouse Look Sensitivity Scale Factor
MouseHipTurnRate(1.f),
MouseHipLookUpRate(1.f),
MouseAimingTurnRate(.2f),
MouseAimingLookUpRate(.2f),
CameraDefaultFOV(0.f),
CameraZoomedFOV(35.f), // Reset in Begin Play
CameraCurrentFOV(0.f),
ZoomedInterpSpeed(20.f),
bAiming(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 180.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 50.f, 50.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	/** Don't rotate when controller rotates */
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll= false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f,540.f,0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	// GetCharacterMovement()->MaxWalkSpeed = 500.f;
	// GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	// GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

// Called when the game starts or when spawned
void ADD_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (FollowCamera)
	{
		CameraDefaultFOV = GetFollowCamera()->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}
	
}

void ADD_CharacterBase::Move(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void ADD_CharacterBase::Look(const FInputActionValue& Value)
{
	const auto LookAxisVector = Value.Get<FVector2D>();
	FVector2D TurnScaleFactor{ LookAxisVector.X * MouseHipTurnRate, LookAxisVector.Y * MouseHipLookUpRate };
	if(bAiming)
	{
		TurnScaleFactor.X = LookAxisVector.X * MouseAimingTurnRate;
		TurnScaleFactor.Y = LookAxisVector.Y * MouseAimingLookUpRate;
	}
	if (Controller != nullptr)
	{
		AddControllerYawInput(TurnScaleFactor.X);
		AddControllerPitchInput(TurnScaleFactor.Y);
	}
}

void ADD_CharacterBase::LookRate(const FInputActionValue& Value)
{
	const auto LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput(LookAxisVector.Y * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ADD_CharacterBase::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Button Pressed : BarrelSocket"));
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),FireSound, GetActorLocation(), GetActorRotation());
	}
	if (const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket"))
	{
		const FTransform BarrelSocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, BarrelSocketTransform);
		}

		FVector BeamEnd;
		if (bool bBeamEnd = GetBeamEndLocation(BarrelSocketTransform.GetLocation(), BeamEnd))
		{
			if (ImpactParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactParticle,BeamEnd);
			}
			if (SmokeTrailParticle)
			{
				UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeTrailParticle, BarrelSocketTransform);
				Beam->SetVectorParameter(FName("Target"), BeamEnd);
			}
		}
		
		/* DEPRECATED: Shoot from gun barrel socket */
		/**
		FHitResult HitResult;
		const FVector Start{ BarrelSocketTransform.GetLocation() };
		const FQuat Rotation{ BarrelSocketTransform.GetRotation() };
		const FVector RotationAxis{ Rotation.GetAxisX() };
		const FVector End{ Start + RotationAxis * 5'000.f };

		FVector BeamEndpoint{ End };
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
			DrawDebugPoint(GetWorld(), HitResult.Location, 5.f, FColor::Orange, false, 2.f);
			BeamEndpoint = HitResult.Location;
			if (ImpactParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactParticle,HitResult.Location);
			}
		}

		if (SmokeTrailParticle)
		{
			UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SmokeTrailParticle, BarrelSocketTransform);
			Beam->SetVectorParameter(FName("Target"), BeamEndpoint);
		}
		*/
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
	}
}

void ADD_CharacterBase::AimButtonPressed()
{
	bAiming = true;
}

void ADD_CharacterBase::AimButtonReleased()
{
	bAiming = false;
}

bool ADD_CharacterBase::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation)
{
	/* Shoot from viewport */
	// Get Current size of viewport
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	
	// Get screen space location of cross-hairs
	FVector2D CrossHairLocation{ ViewportSize.X/2.f, ViewportSize.Y/2.f };
	CrossHairLocation.Y -= 100.f;
	FVector CrossHairWorldPosition;
	FVector CrossHairWorldDirection;

	
	// Get world position and direction of cross-hairs
	if (bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrossHairLocation,
		CrossHairWorldPosition,
		CrossHairWorldDirection))
	{
		FHitResult ScreenTraceHit;
		const FVector Start{ CrossHairWorldPosition };
		const FVector End{ CrossHairWorldPosition + CrossHairWorldDirection * 50'000.f };
		OutBeamLocation = End;
		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, Start, End, ECC_Visibility);
		if (ScreenTraceHit.bBlockingHit)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
			DrawDebugPoint(GetWorld(), ScreenTraceHit.Location, 5.f, FColor::Orange, false, 2.f);
			OutBeamLocation = ScreenTraceHit.Location;
				
		}
		// perform second trace from barrel
			
		FHitResult WeaponTraceHit;
		const FVector WeaponTraceStart{ MuzzleSocketLocation };
		const FVector WeaponTraceEnd{ OutBeamLocation };
		GetWorld()->LineTraceSingleByChannel(WeaponTraceHit, WeaponTraceStart, WeaponTraceEnd, ECC_Visibility);
		if (WeaponTraceHit.bBlockingHit)
		{
			OutBeamLocation = WeaponTraceHit.Location;
		}
		return true;
	}
	return false;
}

void ADD_CharacterBase::InterpCameraZoom(float DeltaTime)
{
	if (bAiming)
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraZoomedFOV, DeltaTime, ZoomedInterpSpeed);
	}
	else
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, DeltaTime, ZoomedInterpSpeed);
	}
	GetFollowCamera()->SetFieldOfView(CameraCurrentFOV);
}

void ADD_CharacterBase::SetLookRates()
{
	if (bAiming)
	{
		BaseTurnRate = AimingTurnRate;
		BaseLookUpRate = AimingLookUpRate;
	}
	else
	{
		BaseTurnRate = HipTurnRate;
		BaseLookUpRate = HipLookUpRate;
	}
}

// Called every frame
void ADD_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpCameraZoom(DeltaTime);
	SetLookRates();
}

// Called to bind functionality to input
void ADD_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADD_CharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADD_CharacterBase::Look);
		EnhancedInputComponent->BindAction(LookRateAction, ETriggerEvent::Triggered, this, &ADD_CharacterBase::LookRate);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &ADD_CharacterBase::FireWeapon);
		EnhancedInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this, &ADD_CharacterBase::AimButtonPressed);
		EnhancedInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this, &ADD_CharacterBase::AimButtonReleased);
	}
}

