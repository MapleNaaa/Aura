// Copyright  by MapleNaaa


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 将运动方向作为角色朝向方向
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true; // 如果为真，移动将被限制在一个平面上。
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 开始时，人物应该贴在地面上

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// AbilitySystemComponent = GetPlayerState()-> 
}

/*
 * 在UE的权威服务器模型中，PossessedBy()主要由服务器触发。
 * 例如，当玩家加入游戏时，服务器会创建一个Pawn并将其控制权分配给对应的玩家控制器，此时服务器自动调用PossessedBy()完成控制权绑定。
 * 客户端不会主动调用此函数，而是通过网络复制机制接收服务器下发的控制权状态变化。
 * 例如，当服务器调用Possess()方法后，客户端会通过OnRep_Controller()或OnRep_PlayerState()等复制函数响应变化，但不会直接触发PossessedBy()本身
 */
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Actor Info on the Server
	InitAbilityActorInfo();
}

/*
 * OnRep_PlayerState()是客户端专属的响应函数,
 * 其设计目的是在客户端检测到PlayerState属性被服务器同步更新后，执行相关的逻辑（如更新UI、播放特效等）。
 * 服务器本身不自动触发此函数，因为服务器始终拥有属性的权威状态，无需通过复制机制响应变化
 */
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init Actor Info on the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState());
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
