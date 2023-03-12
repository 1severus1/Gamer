// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw=false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SringArmComp");
	SpringArmComp->SetupAttachment(RootComponent); 
	SpringArmComp->bUsePawnControlRotation=true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	// The spring arm use the control rot so do the camera
	// which make character move toward the camera forward
	FRotator CtrlRot=GetControlRotation();
	// only care about Yaw. Roll did nothing in getting forward vecter
	CtrlRot.Pitch=0.0f;
	AddMovementInput(CtrlRot.Vector(),value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator CtrlRot=GetControlRotation();
	// compare with MoveForward, Roll will effect the Right vector
	CtrlRot.Pitch=0.0f;
	CtrlRot.Roll=0.0f;
	AddMovementInput(FRotationMatrix(CtrlRot).GetScaledAxis(EAxis::Y),value);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);
	
	// Using Controller Rotation, whitch won't effect the character trans directly
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	
	
	
}

