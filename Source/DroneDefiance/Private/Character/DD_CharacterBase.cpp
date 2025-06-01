// Copyright Chukwuyenum Opone All Rights Reserved


#include "Character/DD_CharacterBase.h"


// Sets default values
ADD_CharacterBase::ADD_CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADD_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADD_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADD_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

