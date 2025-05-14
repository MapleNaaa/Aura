// Copyright by MapleNaaa


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	// 继承于 PlayerController， 通过 GetHitResultAtScreen 实现
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("LastActor: %s"), ToCStr(LastActor.GetName())));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ThisActor: %s"), ToCStr(ThisActor.GetName())));
	
	// 逻辑判断
	if (LastActor != nullptr) LastActor->UnHighlightActor();
	if (ThisActor != nullptr) ThisActor->HighlightActor();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); // 检查指针是否为空，若为空，就中断程序

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	// ULocalPlayer 方便解耦本地玩家的输入、显示与游戏逻辑，支持灵活的单人/多人模式切换，并通过可扩展的接口满足定制化需求
	check(EnhancedInputSubsystem);

	EnhancedInputSubsystem->AddMappingContext(AuraContext,0); // 加入输入上下文

	bShowMouseCursor = true; // 继承于 PlayerController
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// InputComponent 来自于 actor 的继承

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	// BindAction -> 触发函数，按下触发对应函数，类似于 委托
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector2D = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	// pitch 上下   yaw 左右  roll 滚
	// ue是左手系,  pitch -> y轴旋转， yaw -> z轴旋转， roll -> x轴旋转
	
	// GEngine->AddOnScreenDebugMessage(-1,5,FColor::Black, FString::Printf(TEXT("X=%.2f, Y=%.2f"), InputAxisVector2D.X, InputAxisVector2D.Y));

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // axis 单个轴， axes复合轴
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix 将以欧拉角形式的旋转（FRotator）转换为旋转矩阵。

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector2D.Y); 
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector2D.X);
		// 这里有个转化。 输入时， d a -> right, 但是输入轴是 x
		// w s -> up, 但是输入轴是 y
	}
}
