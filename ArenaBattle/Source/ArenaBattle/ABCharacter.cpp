// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ABAnimInstance.h"

// Sets default values
AABCharacter::AABCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimationBlueprint.WarriorAnimationBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> AB_IMC(TEXT("/Game/Book/Input/AB_IMC"));
	if (AB_IMC.Succeeded())
	{
		MappingContext = AB_IMC.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ABA_Move(TEXT("/Game/Book/Input/ABA_Move"));
	if (ABA_Move.Succeeded())
	{
		MoveAction = ABA_Move.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ABA_Look(TEXT("/Game/Book/Input/ABA_Look"));
	if (ABA_Look.Succeeded())
	{
		LookAction = ABA_Look.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ABA_ViewChange(TEXT("/Game/Book/Input/ABA_ViewChange"));
	if (ABA_ViewChange.Succeeded())
	{
		ViewChangeAction = ABA_ViewChange.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ABA_Jump(TEXT("/Game/Book/Input/ABA_Jump"));
	if (ABA_Jump.Succeeded())
	{
		JumpAction = ABA_Jump.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ABA_Attack(TEXT("/Script/EnhancedInput.InputAction'/Game/Book/Input/ABA_Attack.ABA_Attack'"));
	if (ABA_Attack.Succeeded())
	{
		AttackAction = ABA_Attack.Object;
	}

	SetControlMode(EControlMode::GTA);

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	IsAttacking = false;
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		{
			ArmLengthTo = 450.0f;

			SpringArm->bUsePawnControlRotation = true;
			SpringArm->bInheritPitch = true;
			SpringArm->bInheritRoll = true;
			SpringArm->bInheritYaw = true;
			SpringArm->bDoCollisionTest = true;
			bUseControllerRotationYaw = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		}
		break;
	case AABCharacter::EControlMode::DIABLO:
		{
			ArmLengthTo = 800.0f;
			ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);

			SpringArm->bUsePawnControlRotation = false;
			SpringArm->bInheritPitch = false;
			SpringArm->bInheritRoll = false;
			SpringArm->bInheritYaw = false;
			SpringArm->bDoCollisionTest = false;
			bUseControllerRotationYaw = false;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		}
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		{
			__noop;
		}
		break;
	case AABCharacter::EControlMode::DIABLO:
		{
			SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto AnimInstace = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstace)
	{
		AnimInstace->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);
	}
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABCharacter::Look);
		EnhancedInputComponent->BindAction(ViewChangeAction, ETriggerEvent::Started, this, &AABCharacter::ViewChange);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AABCharacter::Attack);
	}
}

void AABCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	switch (CurrentControlMode)
	{
	case AABCharacter::EControlMode::GTA:
		{
			AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), MovementVector.Y); // 카메라의 look 벡터
			AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), MovementVector.X);	// 카메라의 right 벡터
		}
		break;
	case AABCharacter::EControlMode::DIABLO:
		{
			DirectionToMove.X = MovementVector.Y;
			DirectionToMove.Y = MovementVector.X;
		}
		break;
	}
}

void AABCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		switch (CurrentControlMode)
		{
		case AABCharacter::EControlMode::GTA:
			{
				// add yaw and pitch input to controller
				AddControllerPitchInput(LookAxisVector.Y);
				AddControllerYawInput(LookAxisVector.X);
			}
			break;
		case AABCharacter::EControlMode::DIABLO:
			{
				__noop;
			}
			break;
		}
	}
}

void AABCharacter::ViewChange(const FInputActionValue& Value)
{
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftShift))
	{
		UE_LOG(LogTemp, Warning, TEXT("Shift + V Pressed!"));
		switch (CurrentControlMode)
		{
		case AABCharacter::EControlMode::GTA:
			{
				GetController()->SetControlRotation(GetActorRotation());
				SetControlMode(EControlMode::DIABLO);
			}
			break;
		case AABCharacter::EControlMode::DIABLO:
			{
				GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
				SetControlMode(EControlMode::GTA);
			}
			break;
		}
	}
}

void AABCharacter::Attack(const FInputActionValue& Value)
{
	ABLOG_S(Warning);
	if (IsAttacking)
		return;
	
	auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	AnimInstance->PlayAttackMontage();
	IsAttacking = true;
}

void AABCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{	
	ABLOG_S(Warning);

	IsAttacking = false;
}

