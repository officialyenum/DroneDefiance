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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
